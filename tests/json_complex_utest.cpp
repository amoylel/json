#include "./../json.hpp"


#include "./utest.hpp"
#include "./make_json.hpp"

TEST(json_complex, string) {


    json_type json = amo::string_reader{ "[\"\\\"foo\\\"\"]" };
    EXPECT_EQ(json[0].get<std::string>(), "\"foo\"");
    
    
}

TEST(json_complex, number) {

    EXPECT_EQ(json_type(amo::string_reader{ "1.1" }), 1.1);
    EXPECT_EQ(json_type(amo::string_reader{ "12.34" }), 12.34);
    EXPECT_EQ(json_type(amo::string_reader{ "1234.567" }), 1234.567);
    EXPECT_EQ(json_type(amo::string_reader{ "1234.5671e0" }), 1234.5671);
    EXPECT_EQ(json_type(amo::string_reader{ "1234.5671e1" }), 12345.671);
    EXPECT_EQ(json_type(amo::string_reader{ "1e1" }), 10);
    EXPECT_EQ(json_type(amo::string_reader{ "10e307" }), 1e308);
    EXPECT_EQ(json_type(amo::string_reader{ "5e-324" }), 0.0);
}

TEST(json_complex, parse) {
    // create JSON object
    json_type fields;
    fields["one"] = ("one");
    fields["two"] = ("two three");
    fields["three"] = ("three \"four\"");
    
    std::string payload = fields.to_string();
    json_type parsed_fields = amo::string_reader(payload);
    
    EXPECT_TRUE(parsed_fields["one"] == fields["one"]);
    EXPECT_TRUE(parsed_fields["two"] == fields["two"]);
    EXPECT_TRUE(parsed_fields["three"] == fields["three"]);
    
    EXPECT_TRUE(parsed_fields["one"] == std::string("one"));
    EXPECT_TRUE(parsed_fields["two"] == std::string("two three"));
    EXPECT_TRUE(parsed_fields["three"] == std::string("three \"four\""));
    
    // check equality of the objects
    EXPECT_TRUE(parsed_fields == fields);
    
    // check equality of the serialized objects
    EXPECT_TRUE(fields.to_string() == parsed_fields.to_string());
    
    // check everything in one line
    EXPECT_TRUE(fields == json_type(amo::string_reader(fields.to_string())));
}

TEST(json_complex, nonstandard_number) {
    json_type json = 4294967296U;
    uint32_t u = json; //Òç³ö
    EXPECT_EQ(u, 0);
    json = amo::string_reader("4294967296");
    EXPECT_TRUE(json.get<float>() == 4294967296.0f);
    json = -2147483649LL;
    EXPECT_TRUE(json.get<int32_t>() == 2147483647);
    json = amo::string_reader("-2147483649");
    EXPECT_TRUE(json.get<float>() == -2147483650.0f);
}

TEST(json_complex, binary_string) {
    int64_t number = 10;
    std::string bytes{ "\x00" "asdf\n", 6 };
    json_type j;
    j["int64"] = number;
    j["binary string"] = bytes;
    // make sure the number is really printed as decimal "10" and not as
    // hexadecimal "a"
    
    std::string str = j.to_string();
    std::string str2("{\"int64\":10,\"binary string\":\"\0asdf\n\"}", 37);
    EXPECT_EQ(j.to_string(), str2);
    
    
    json_type o = { {"name", "value"} };
    
    std::string s1 = o["name"];
    EXPECT_TRUE(s1 == "value");
    
    std::string s2;
    s2 = o["name"].get<std::string>();
    
    EXPECT_TRUE(s2 == "value");
}

TEST(json_complex, floating_point_parse) {
    json_type j;
    std::cout << (std::numeric_limits<double>::max)() << std::endl;
    std::cout << (std::numeric_limits<double>::min)() << std::endl;
    j = amo::string_reader("-0.0");
    EXPECT_TRUE(j.get<double>() == -0.0);
    double d = 2.2 * 1e307;
    double d3 = 0.00001;
    std::cout << 1e-5 * 1e5 << std::endl;
    std::cout << 1e-5 << std::endl;
    std::cout << 1e5 << std::endl;
    j = amo::string_reader("2.22507385850720113605740979670913197593481954635164564e-308");
    double d0 = 2.22507385850720113605740979670913197593481954635164564e-308;
    double d1 = j;
    double d2 = 2.2250738585072009e-308;
    std::cout << fabs(d1 - d2) << std::endl;
    EXPECT_TRUE(j.get<double>() == 2.2250738585072009e-308);
    
    j = amo::string_reader("0.999999999999999944488848768742172978818416595458984374");
    d1 = j;
    d2 = 0.99999999999999989;
    std::cout << fabs(d1 - d2) << std::endl;
    EXPECT_TRUE(fabs(j.get<double>() - 0.99999999999999989) < 1e-6);
    
    j = amo::string_reader("1.00000000000000011102230246251565404236316680908203126");
    
    d1 = j;
    d2 = 1.00000000000000022;
    std::cout << fabs(d1 - d2) << std::endl;
    
    
    j = amo::string_reader("720575e-5");
    d1 = j;
    d2 = 720575.0;
    
    std::cout << fabs(d1 - d2) << std::endl;
    EXPECT_TRUE(j.get<double>() == 7.20575);
    
    EXPECT_TRUE(fabs(j.get<double>() - (720575e-5)) < 1e-6);
    j = amo::string_reader("7205759403792793199999e-5");
    d1 = j;
    d2 = 7205759403792793199999e-5;
    
    
    std::cout << fabs(d1 - d2) << std::endl;
    EXPECT_TRUE(fabs(1 - j.get<double>() / 7205759403792793199999e-5) < 1e-15);
    
    j = amo::string_reader("922337203685477529599999e-5");
    d1 = j;
    d2 = 9223372036854774784.0;
    std::cout << fabs(d1 - d2) << std::endl;
    EXPECT_TRUE(j.get<double>() == 9223372036854774784.0);
    
    j = amo::string_reader("1014120480182583464902367222169599999e-5");
    d1 = j;
    d2 = 10141204801825834086073718800384.0;
    std::cout << fabs(d1 - d2) << std::endl;
    EXPECT_TRUE(fabs(1 - j.get<double>() / 10141204801825834086073718800384.0) < 1e-15);
    std::string ss = "5708990770823839207320493820740630171355185151";
    uint64_t result = 0;
    double result2 = 0.0;
    double result3 = 0.0;
    double result4 = 0.0;
    uint64_t dd1 = 0;
    uint64_t dd2 = 0;
    std::array<double, 10> dict = { 0.000001, 0.000002, 0.000003, 0.000004, 0.000005, 0.000006, 0.000007, 0.000008, 0.000009 };
    
    j = amo::string_reader("5708990770823839207320493820740630171355185151999e-3");
    d1 = j;
    d2 = 5708990770823839207320493820740630171355185151.0;
    std::cout << fabs(d1 - d2) << std::endl;
    EXPECT_TRUE(j.get<double>() == 5708990770823839207320493820740630171355185151.0);
    
    // create JSON class with nonstandard float number type
    
    // float
    json_type j_float =  1.23e25f;
    EXPECT_TRUE(j_float.get<float>() == 1.23e25f);
    
    // double
    json_type j_double = 1.23e35;
    EXPECT_TRUE(j_double.get<double>() == 1.23e35);
    
    // long double
    json_type j_long_double = 1.23e45L;
    double db = j_long_double.get<double>();
    long double ldb = j_long_double.get<long double>();
    std::cout << typeid(db).name() << ":  " << sizeof(db) << std::endl;
    std::cout << typeid(ldb).name() << ":  " << sizeof(ldb) << std::endl;
    std::cout << db << ", " << ldb << std::endl;
    
    if (db == ldb) {
        std::cout << "dd" << std::endl;
    }
    auto dd = 1.0 - fabs(db / ldb);
    std::cout << dd << std::endl;
    EXPECT_TRUE(1 - fabs(j_long_double.get<long double>() / 1.23e45L) < 1e-15);
    
    
    
    json_type j1 = amo::string_reader("1000000000000000010E5");
    std::string s1 = j1.to_string();
    json_type j2 = amo::string_reader(s1);
    std::string s2 = j2.to_string();
    EXPECT_TRUE((1 - j1.get<double>() / j2.get<double>()) < 1e-15);
}