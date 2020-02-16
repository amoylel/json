#include "./../json.hpp"


#include "./utest.hpp"
#include "./make_json.hpp"
#include <limits>
#include <random>

#define DOUBLE_NUMBER_TEST(val ) EXPECT_TRUE(number_test(val, #val))

bool number_test(double number, const std::string& str) {
    //std::string str = std::dtoa(number);
    json_type json = amo::string_reader{ str };
    double d = json.get<double>();
    
    if (fabs(d - number) < 1e-12) {
        return true;
    } else {
        std::cout << __FUNCTION__ << " not eq : " << d << " vs " << number << std::endl;
        std::cout << __FUNCTION__ << " not eq : " << std::to_string(d) << " vs " << std::to_string(number) << std::endl;
    }
    
    return (json == number);
    //(d == number);
}

TEST(json, stream) {
    amo::json json = make_json2();
    std::cout << json << std::endl;
    std::string str;
    str << json;
    std::cout << str << std::endl;
    std::stringstream stream;
    stream << json;
    std::cout << stream.str() << std::endl;
}


TEST(json, ttttttttttttt) {

    json_type custom1 = amo::custom_class("2341");
    std::string s11 = custom1.to_string();
    
    json_type json2 = amo::string_reader{ s11 };
    json2.to_file("./aaa11.json");
    
    json_type json3 = amo::file_reader("./aaa11.json");
    
    auto c11 = json3.get<amo::custom_class>();
}

TEST(json, number_test) {

    std::string sb = "123456789123456789";
    double kkk = 0;
    
    for (auto& p : sb) {
        kkk = kkk * 10 + p - '0';
        
    }
    
    double d53 = (double)123456789123456789;
    uint64_t md = 123456789123456789;
    uint64_t md4 = (std::numeric_limits<uint64_t>::max)();
    double md44 = static_cast<double>(md4);
    double d0 = 1.41270412262646923e308;
    double d1 = 12.4127041226264692e307;
    double d2 = 123.4127041226264692e306;
    double d3 = 1234.4127041226264692e305;
    double d4 = 12345.4127041226264692e304;
    double d5 = 123456.4127041226264692e303;
    double d6 = 1234567.4127041226264692e302;
    DOUBLE_NUMBER_TEST(0.0);
    DOUBLE_NUMBER_TEST(0.1);
    DOUBLE_NUMBER_TEST(0.123456);
    DOUBLE_NUMBER_TEST(0.123456789);
    DOUBLE_NUMBER_TEST(0.123456789123456789);
    DOUBLE_NUMBER_TEST(123.0)
    DOUBLE_NUMBER_TEST(123.45)
    DOUBLE_NUMBER_TEST(123.456789123456789123456789);
    DOUBLE_NUMBER_TEST(
        56228814507681166731141408327015820580548167022761983334891602262095210814983865078797196717147971071509827443744672166088692394682481829047792459121536380174248635504760624549101532717325128361290239569375854640122074021229462585808559573764043263459382884154148249063113220261980374589751727712226739486720.000000);
        
    DOUBLE_NUMBER_TEST(0.0e10);
    DOUBLE_NUMBER_TEST(0.1e10);
    DOUBLE_NUMBER_TEST(0.123456e10);
    DOUBLE_NUMBER_TEST(0.123456789e10);
    DOUBLE_NUMBER_TEST(0.123456789123456789e10);
    DOUBLE_NUMBER_TEST(123.0e10)
    DOUBLE_NUMBER_TEST(123.45e10)
    DOUBLE_NUMBER_TEST(123.456789123456789123456789e10);
}
TEST(json, construct_int8_t) {
    typedef int8_t value_type;
    
    for (int i = (std::numeric_limits<value_type>::min)(); i < (std::numeric_limits<value_type>::max)(); ++i) {
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
}

TEST(json, construct_uint8_t) {
    typedef uint8_t value_type;
    
    for (int i = (std::numeric_limits<value_type>::min)(); i < (std::numeric_limits<value_type>::max)(); ++i) {
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
}

TEST(json, construct_int16_t) {
    typedef int16_t value_type;
    
    for (value_type i = (std::numeric_limits<value_type>::min)(); i < (std::numeric_limits<value_type>::max)(); ++i) {
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
}

TEST(json, construct_uint16_t) {
    typedef uint16_t value_type;
    
    for (value_type i = (std::numeric_limits<value_type>::min)(); i < (std::numeric_limits<value_type>::max)(); ++i) {
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
}

TEST(json, construct_int32) {
    typedef int32_t value_type;
    std::random_device rng;
    
    value_type m_min = (std::numeric_limits<value_type>::min)();
    value_type m_max = (std::numeric_limits<value_type>::max)();
    std::uniform_int_distribution<value_type> gen(m_min, m_max);
    
    std::vector<value_type> vec = { m_min, m_max };
    
    // 边界
    for (size_t i = 0; i < vec.size(); ++i) {
    
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
    
    
    for (size_t index = 0; index < 1000000; ++index) {
        value_type i = gen(rng);
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
        i = -i;
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
}


TEST(json, construct_uint32) {
    typedef uint32_t value_type;
    std::random_device rng;
    
    value_type m_min = (std::numeric_limits<value_type>::min)();
    value_type m_max = (std::numeric_limits<value_type>::max)();
    std::uniform_int_distribution<value_type> gen(m_min, m_max);
    
    std::vector<value_type> vec = { m_min, m_max };
    
    // 边界
    for (size_t i = 0; i < vec.size(); ++i) {
    
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
    
    
    for (size_t index = 0; index < 1000000; ++index) {
        value_type i = gen(rng);
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
}

TEST(json, construct_int64) {
    typedef int64_t value_type;
    std::random_device rng;
    
    value_type m_min = (std::numeric_limits<value_type>::min)();
    value_type m_max = (std::numeric_limits<value_type>::max)();
    std::uniform_int_distribution<value_type> gen(m_min, m_max);
    
    std::vector<value_type> vec = { m_min, m_max };
    
    // 边界
    for (size_t i = 0; i < vec.size(); ++i) {
    
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
    
    
    for (size_t index = 0; index < 1000000; ++index) {
        value_type i = gen(rng);
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
        
        i = -1;
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
        
    }
}

TEST(json, construct_uint64) {
    typedef uint64_t value_type;
    std::random_device rng;
    
    value_type m_min = (std::numeric_limits<value_type>::min)();
    value_type m_max = (std::numeric_limits<value_type>::max)();
    std::uniform_int_distribution<value_type> gen(m_min, m_max);
    
    std::vector<value_type> vec = { m_min, m_max };
    
    // 边界
    for (size_t i = 0; i < vec.size(); ++i) {
    
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
    
    
    for (size_t index = 0; index < 1000000; ++index) {
        value_type i = gen(rng);
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
        
    }
}

TEST(json, construct_float) {
    typedef float value_type;
    std::random_device rng;
    
    value_type m_min = (std::numeric_limits<value_type>::min)();
    value_type m_max = (std::numeric_limits<value_type>::max)();
    std::uniform_real_distribution<value_type> gen(m_min, m_max);
    
    std::vector<value_type> vec = { m_min, m_max };
    
    // 边界
    for (size_t i = 0; i < vec.size(); ++i) {
    
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
    
    
    for (size_t index = 0; index < 1000000; ++index) {
        value_type i = gen(rng);
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
        
        i = -i;
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
}

TEST(json, construct_double) {
    typedef double value_type;
    std::random_device rng;
    
    value_type m_min = (std::numeric_limits<value_type>::min)();
    value_type m_max = (std::numeric_limits<value_type>::max)();
    std::uniform_real_distribution<value_type> gen(m_min, m_max);
    
    std::vector<value_type> vec = { m_min, m_max, 9007199254740992, 9007199254740991, -9007199254740991, -9007199254740992 };
    
    // 边界
    for (size_t i = 0; i < vec.size(); ++i) {
    
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
    
    
    for (size_t index = 0; index < 100000; ++index) {
        value_type i = gen(rng);
        //EXPECT_EQ(json_type(i), i);
        double b = json_type(amo::string_reader{ std::to_string(i) });
        double bc = fabs(1.0 - b / i) ;
        EXPECT_TRUE(fabs(1.0 - b / i) < 1e-15);
        //EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
}

TEST(json, construct_double2) {
    typedef double value_type;
    std::random_device rng;
    
    value_type m_min = (std::numeric_limits<value_type>::min)();
    value_type m_max = (std::numeric_limits<value_type>::max)();
    std::uniform_int_distribution<int> gen(0, 16);
    std::vector<value_type> vec = { m_min, m_max };
    std::vector< std::uniform_int_distribution<uint64_t> >  gens;
    gens.push_back(std::uniform_int_distribution<uint64_t>(0, 0));
    for (int i = 0; i < 16; ++i) {
        gens.push_back(std::uniform_int_distribution<uint64_t>((uint64_t)::pow(10, i), (uint64_t)::pow(10, (i + 1))));
    }
    
    
    // 边界
    for (size_t i = 0; i < vec.size(); ++i) {
    
        EXPECT_EQ(json_type(i), i);
        EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
    
    for (size_t index = 0; index < 1000000; ++index) {
        int float_part = gen(rng);
        uint64_t v = gens[16](rng);
        double i = v / pow(10, float_part);
        EXPECT_EQ(json_type(i), i);
        std::string ss = amo::to_string(i);
        json_type json = amo::string_reader{ ss };
        double b = json;
        EXPECT_TRUE(fabs(1.0 - b / i) < 1e-15);
        
        i = -1;
        ss = amo::to_string(i);
        json = amo::string_reader{ ss };
        b = json;
        EXPECT_TRUE(fabs(1.0 - b / i) < 1e-15);
    }
}


TEST(json, construct_with_default) {
    // 默认构造函数
    json_type json;  // 空对象
    EXPECT_EQ(json.get_type(), amo::json_value_empty);
    
}

TEST(json, construct_with_empty_t) {
    json_type json = {};
    EXPECT_EQ(json.get_type(), amo::json_value_empty);
}

TEST(json, construct_value_t) {
    // 默认构造函数
    json_type json1(amo::json_value_object);  // JsonObject
    EXPECT_EQ(json1.get_type(), amo::json_value_object);
    
    json_type json2(amo::json_value_array);  // JsonArray
    EXPECT_EQ(json2.get_type(), amo::json_value_array);
    
    // 后面的不建议使用，只是设置了类型，具体取值不确定(内存没有置0)
    json_type json3(amo::json_value_boolean);
    json_type json4(amo::json_value_integer);
    json_type json5(amo::json_value_float);
    json_type json6(amo::json_value_string);
}


TEST(json, construct_assignment) {
    // 赋值构造函数
    json_type json1 = true;
    json_type json2 = false;
    json_type json3 = nullptr;
    json_type json4 = 1;
    json_type json5 = 111LL;
    json_type json6 = (std::numeric_limits<uint32_t>::max)();
    json_type json7 = (std::numeric_limits<uint64_t>::max)();
    json_type json8 = (std::numeric_limits<int64_t>::min)();
    json_type json9 = (std::numeric_limits<int64_t>::min)();
    json_type json10 = 1.0;		// double
    json_type json11 = 1.0f;    // float
    json_type json12 = (std::numeric_limits<double>::max)();
    json_type json13 = "abcdefg";	// const char*
    json_type json14 = std::string("abcdefg");  // std::string
    json_type json15 = u8"kd wer\\r\\n中方式\\u3053\\u3093\\u306b\\u3061\\u306f\\u4e16\\u754c\\uff0112312中文";
    
    char abc[4] = "123";
    
    json_type json16 = 'c';  // int8_t
    char c = json16;
    json_type json17 = abc;
    
    EXPECT_EQ(json1.get_type(), amo::json_value_boolean);
    EXPECT_EQ(json2.get_type(), amo::json_value_boolean);
    EXPECT_EQ(json3.get_type(), amo::json_value_null);
    EXPECT_EQ(json4.get_type(), amo::json_value_integer);
    EXPECT_EQ(json5.get_type(), amo::json_value_integer);
    EXPECT_EQ(json6.get_type(), amo::json_value_unsigned);
    EXPECT_EQ(json7.get_type(), amo::json_value_unsigned);
    EXPECT_EQ(json8.get_type(), amo::json_value_integer);
    EXPECT_EQ(json9.get_type(), amo::json_value_integer);
    EXPECT_EQ(json10.get_type(), amo::json_value_float);
    EXPECT_EQ(json11.get_type(), amo::json_value_float);
    EXPECT_EQ(json12.get_type(), amo::json_value_float);
    EXPECT_EQ(json13.get_type(), amo::json_value_string);
    EXPECT_EQ(json14.get_type(), amo::json_value_string);
    EXPECT_EQ(json15.get_type(), amo::json_value_string);
    EXPECT_EQ(json16.get_type(), amo::json_value_integer);
    EXPECT_EQ(json17.get_type(), amo::json_value_string);
}


TEST(json, construct_inner_copy) {
    // 复制构造
    // copy
    json_type json1 = make_json2();
    json_type json2 = json1["m_bool"];
    json2 = 3;
    EXPECT_EQ(json1["m_bool"], 3);
}

TEST(json, construct_copy) {
    // 复制构造
    // copy
    json_type json1 = make_json2();
    // copy ，将json1中的数据复制一份到json2中
    json_type json2 = json1;
    std::string str1 = json1.to_string();
    std::string str2 = json2.to_string();
    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;
    EXPECT_EQ(json2.to_string(), json1.to_string());
    json2["aaa"] = 3;
    EXPECT_NE(json2.to_string(), json1.to_string());
    
    json_type json3 = 4;
    json_type json4 = (json3);
    EXPECT_EQ(json3.get<int>(), json4.get<int>());
    json4 = 5;
    EXPECT_NE(json3.get<int>(), json4.get<int>());
    json3 = true;
    EXPECT_NE(json4.is<bool>(), true);
    EXPECT_EQ(json3.is<bool>(), json4.is<int>());
    
}

TEST(json, construct_move) {
    // 移动构造
    // move
    json_type json1 = make_json2();
    // move 使用std::move 强制转换为右值, 将json1中的数据移动到json2中
    json_type json2 = std::move(json1);
    EXPECT_EQ(json2.to_string(), json1.to_string());
    json2["aaa"] = 3;
    EXPECT_EQ(json2.to_string(), json1.to_string());
    json_type json3 = 4;
    json_type json4 = std::move(json3);
    EXPECT_EQ(json3.get<int>(), json4.get<int>());
    json4 = 5;
    EXPECT_EQ(json3.get<int>(), json4.get<int>());
    json3 = true;
    EXPECT_EQ(json4.is<bool>(), true);
    EXPECT_EQ(json3.get<bool>(), json4.get<bool>());
}


TEST(json, construct_parse_string) {
    // 通过解析字符串或流来构造JSON对象
    json_type json1 = amo::string_reader("{ \"aaa\":3, \"bbb\":\"3.0\", \"ccc\":true,\"ddd\":null }");
    std::stringstream sstream("{ \"aaa\":3, \"bbb\":\"3.0\", \"ccc\":true,\"ddd\":null } ");
    json_type json2 = sstream;
    EXPECT_EQ(json1.to_string(), json2.to_string());
    std::fstream ifstream("test.json", std::ios::in);
    json_type json3(ifstream);
    
    
    json_type json4(amo::string_reader("true"));
    json_type json5(amo::string_reader("false"));
    json_type json6(amo::string_reader("null"));
    json_type json7(amo::string_reader("1"));
    json_type json8(amo::string_reader("-1.2"));
    json_type json9(amo::string_reader("\"string \\\"string\""));
    json_type json10(amo::string_reader(R"({"aaa": 1})"));
    json_type json11(amo::string_reader("{}"));
    json_type json12(amo::string_reader("[1]"));
    json_type json13(amo::string_reader("[]"));
    
    EXPECT_EQ(json4.get_type(), amo::json_value_boolean);
    EXPECT_EQ(json5.get_type(), amo::json_value_boolean);
    EXPECT_EQ(json6.get_type(), amo::json_value_null);
    EXPECT_EQ(json7.get_type(), amo::json_value_unsigned);
    EXPECT_EQ(json8.get_type(), amo::json_value_float);
    EXPECT_EQ(json9.get_type(), amo::json_value_string);    // lite 模式下解析错误
    EXPECT_EQ(json10.get_type(), amo::json_value_object);
    EXPECT_EQ(json11.get_type(), amo::json_value_object);
    EXPECT_EQ(json12.get_type(), amo::json_value_array);
    EXPECT_EQ(json13.get_type(), amo::json_value_array);
    
}

TEST(json, construct_parse_file) {
    json_type json = make_json2();
    json.to_file("./file.json");
    json_type json2 = amo::file_reader{ "./file.json" };
    EXPECT_EQ(json.to_string(), json2.to_string());
}

TEST(json, construct_initializer_list) {
    // 使用成员初始化器列表
    // 被初始化为JsonArray
    json_type json1 = { std::string("bbb"), 12, "ccc", 3423, "123", "aaa", true, 2.34, std::nullptr_t(), nullptr };
    
    EXPECT_EQ(json1.is_array(), true);
    EXPECT_EQ(json1[3].get<int>(), 3423);
    EXPECT_EQ(json1[1], 12);
    
    // 只有两个元素的{string, any}会被解析成JsonObject
    EXPECT_EQ(json_type{ "key", 1 } .is_object(), true);
    EXPECT_EQ(json_type{ 1, "value" } .is_array(), true);
    EXPECT_EQ(json_type{ "key", 1, 2 } .is_array(), true);
    // 插入空值，将JsonObject强制解析为JsonArray
    EXPECT_EQ(json_type{ "key", 1, {} } .is_array(), true);
    EXPECT_EQ(json_type{ "key", {}, 1 } .is_array(), true);
    EXPECT_EQ(json_type{ {}, "key", 1 } .is_array(), true);
    // 空值不会被解析，不会影响其他值的顺序
    EXPECT_EQ(json_type{ {}, "key", 1 } .operator[](0), std::string("key"));
    EXPECT_EQ(json_type{ {}, {}, {}, "key", 1 } [1], 1);
    
    // 键值对被初始化为JsonObject
    json_type json211 = {
        {"aaa", 1}
    };
    
    EXPECT_EQ(json211.is_object(), true);
    // 键值对，JSONObject
    json_type json2 = {
        {"aaa", 1},
        {"bbb", std::string("bbb")},
        {
            "ccc", {
                {"aaa", 1},
                {"bbb", std::string("bbb")},
                {"ccc", {std::string("bbb"), 1, 2, 3, 4, 5}}
            }
        }
    };
    
    std::string str2 = json2.to_string();
    std::cout << str2 << std::endl;
    EXPECT_EQ(json2.is_object(), true);
    EXPECT_EQ(json2["ccc"]["aaa"], 1);
    // 在键值对中加入空JSON，强转为JsonArray
    json_type json3 = {
        {{"aaa", 1}},
        {{"bbb", std::string("000")}},
        {
            "ccc", {
                {"ddd", 1},
                {"eee", std::string("fff")}
            }
        },
        ""_json_
    };
    std::string json3str = json3.to_string();
    std::cout << json3str << std::endl;
    EXPECT_EQ(json3.is_array(), true);
    EXPECT_EQ(json3[2]["ccc"]["ddd"].get<int>(), 1);
    
    // 复杂JsonArray
    json_type json5 = { 1, 2, 3, { {"aaa", 1}, {"bbb", {1, 2, 3, 4, 5}} }, { "aaa", 1, "bbb", {1, 2, 3, 4, 5} }, "ccc" };
    
    EXPECT_EQ(json5.is_array(), true);
    EXPECT_EQ(json5[3]["bbb"][0].get<int>(), 1);
}

TEST(json, construct_pair) {
    json_type json = std::pair<std::string, int > { "1", 1};
    std::cout << json.to_string() << std::endl;
    
    json_type json2 = std::pair<bool, int > { false, 1 };
    std::cout << json2.to_string() << std::endl;
}

TEST(json, construct_vector) {
    json_type json = std::vector<int> { 1, 2, 3, 4, 5 };
    std::cout << json.to_string() << std::endl;
}

TEST(json, construct_list) {
    json_type json = std::list<int> { 1, 2, 3, 4, 5 };
    std::cout << json.to_string() << std::endl;
}

TEST(json, construct_set) {
    json_type json = std::set<int> { 1, 2, 3, 4, 5 };
    std::cout << json.to_string() << std::endl;
}

TEST(json, construct_deque) {
    json_type json = std::deque<int> { 1, 2, 3, 4, 5 };
    std::cout << json.to_string() << std::endl;
}

TEST(json, construct_map) {
    json_type json = std::map<std::string, int> { {"1", 1}, {"2", 2}, {"3", 3 }, {"4", 4}, {"5", 5} };
    std::cout << json.to_string() << std::endl;
    
    json_type json2 = std::map<double, int> { {1, 1}, {2, 2}, {3, 3 }, {4, 4}, {5, 5} };
    std::cout << json2.to_string() << std::endl;
}

TEST(json, construct_custom_json_value) {

    json_type json31;
    json31.set_object();
    json31["1"] = make_json2();
    json_type sbu = json31["1"];
    sbu = 4;
    json_type sb2 = json31["1"].get<json_type>();
    sb2 = 3;
    std::string str1 = json31.to_string();
    std::string str2 = sb2.to_string();
    std::string str3 = sbu.to_string();
    json_type jsonc = make_json2();
    
    json_type custom1 = amo::custom_class("2341");
    std::string s11 = custom1.to_string();
    
    json_type json2 = amo::string_reader{ s11 };
    json2.to_file("./aaa11.json");
    auto t1 = json2.get_type();
    json_type json3 = amo::file_reader("./aaa11.json");
    
    auto c11 = json3.get<amo::custom_class>();
    std::cout << s11 << std::endl;
    EXPECT_EQ(custom1.is<amo::custom_class>(), true);
    EXPECT_EQ(custom1.is<int>(), false);
    amo::custom_class c1 = custom1;
    std::string str = custom1.to_string();
    json_type::ObjectType object("23423");
    std::string aaa("aaa");
    //std::vector<json_type::ObjectType> vec { std::string("bbb"),12, "ccc", 3423, "123", aaa, true, 2.34, std::nullptr_t(), nullptr };
    json_type custom3 = { std::string("bbb"), 12, "ccc", 3423, "123", aaa, true, 2.34, std::nullptr_t(), nullptr };
    std::string sb3 = custom3.to_string();
    json_type custom4 = {
        {"aaa", 1},
        {"bbb", std::string("bbb")},
        {
            "ccc", {
                {"aaa", 1},
                {"bbb", std::string("bbb")}
            },
        },
        ""_json_
    };
    std::string sb4 = custom4.to_string();
    
    json_type custom5 = amo::custom_class2("11");
    amo::custom_class2 class2 = custom5;
    std::string sss = custom5.to_string();
    amo::custom_class custom6 = custom5;
}


#include <forward_list>
#include <stack>
#include <queue>

template<typename T>
class custrom_seq_container {
public:
    typedef std::iterator<std::bidirectional_iterator_tag, T> iterator;
    iterator begin() { return iterator(); }
    iterator end() { return iterator(); }
};

template<typename key_type, typename value_type = key_type>
static void test_is_maybe_sequence_containter(bool& utest_passed) {

    std::cout << typeid(value_type).name() << std::endl;
    typedef std::array<value_type, 10> T;
    
    typedef typename _AMO has_declare_iterator<T>::type iterator;
    typedef typename _AMO has_declare_iterator_category<iterator>::type iterator_category;
    auto a1 = std::is_class<T>::value;
    auto a2 = _AMO has_member_function_begin<T>::value;
    auto a3 = _AMO has_member_function_end<T>::value;
    auto a4 = _AMO has_declare_iterator<T >::value;
    auto a5 = _AMO has_declare_iterator_category<iterator>::value;
    auto a6 = std::is_convertible<iterator_category, std::input_iterator_tag>::value;
    std::cout << "a1:" << a1 << std::endl;
    std::cout << "a2:" << a2 << std::endl;
    std::cout << "a3:" << a3 << std::endl;
    std::cout << "a4:" << a4 << std::endl;
    std::cout << "a5:" << a5 << std::endl;
    std::cout << "a6:" << a6 << std::endl;
    
    using namespace amo;
    EXPECT_FALSE(is_maybe_sequence_container<bool>::value);
    EXPECT_FALSE(is_maybe_sequence_container<int>::value);
    EXPECT_FALSE(is_maybe_sequence_container<double>::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::nullptr_t>::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::function<void(bool)>>::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::stack<value_type> >::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::queue<value_type> >::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::priority_queue<value_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container<std::string>::value);
    EXPECT_TRUE(is_maybe_sequence_container<custrom_seq_container<value_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::array<value_type, 10>>::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::vector<value_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::deque<value_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::forward_list<value_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::list<value_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::set<key_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::multiset<key_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::map<key_type, value_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::multimap<key_type, value_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::unordered_set<key_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::unordered_map<key_type, value_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::unordered_multiset<key_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::unordered_multimap<key_type, value_type>>::value);
}

template<typename key_type, typename value_type = key_type>
static void test_is_array(bool& utest_passed) {
    using namespace amo;
    EXPECT_FALSE(is_maybe_sequence_container<bool>::value);
    EXPECT_FALSE(is_maybe_sequence_container<int>::value);
    EXPECT_FALSE(is_maybe_sequence_container<double>::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::nullptr_t>::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::function<void(bool)>>::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::stack<value_type> >::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::queue<value_type> >::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::priority_queue<value_type> >::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::string>::value);
    EXPECT_FALSE(is_maybe_sequence_container<custrom_seq_container<value_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::array<value_type, 10>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::vector<value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::deque<value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::forward_list<value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::list<value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::set<value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::multiset<value_type> >::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::map<key_type, value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::multimap<key_type, value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::unordered_set<value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::unordered_map<key_type, value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::unordered_multiset<key_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::unordered_multimap<key_type, value_type>>::value);
}

template<typename key_type, typename value_type = key_type>
static void test_is_vector(bool& utest_passed) {
    using namespace amo;
    std::cout << __FUNCTION__ << ": \t key_type: " << typeid(key_type).name() << ", value_type: " << typeid(
                  value_type).name() << std::endl;
    EXPECT_FALSE(is_vector<bool>::value);
    EXPECT_FALSE(is_vector<int>::value);
    EXPECT_FALSE(is_vector<double>::value);
    EXPECT_FALSE(is_vector<std::nullptr_t>::value);
    EXPECT_FALSE(is_vector<std::function<void(bool)>>::value);
    EXPECT_FALSE(is_vector<std::stack<value_type> >::value);
    EXPECT_FALSE(is_vector<std::queue<value_type> >::value);
    EXPECT_FALSE(is_vector<std::priority_queue<value_type> >::value);
    EXPECT_FALSE(is_vector<std::string>::value);
    EXPECT_FALSE(is_vector<custrom_seq_container<value_type> >::value);
    EXPECT_FALSE(is_vector < std::array<value_type, 10>>::value);
    EXPECT_TRUE(is_vector < std::vector<value_type>>::value);
    EXPECT_FALSE(is_vector < std::deque<value_type>>::value);
    EXPECT_FALSE(is_vector < std::forward_list<value_type>>::value);
    EXPECT_FALSE(is_vector < std::list<value_type>>::value);
    EXPECT_FALSE(is_vector < std::set<key_type>>::value);
    EXPECT_FALSE(is_vector < std::multiset<key_type> >::value);
    EXPECT_FALSE(is_vector < std::map<key_type, value_type>>::value);
    EXPECT_FALSE(is_vector < std::multimap<key_type, value_type>>::value);
    EXPECT_FALSE(is_vector < std::unordered_set<key_type>>::value);
    EXPECT_FALSE(is_vector < std::unordered_map<key_type, value_type>>::value);
    EXPECT_FALSE(is_vector < std::unordered_multiset<key_type>>::value);
    EXPECT_FALSE(is_vector < std::unordered_multimap<key_type, value_type>>::value);
}

#ifndef AMO_TYPE_TRAITS_CONTAINER_TEST
#define AMO_TYPE_TRAITS_CONTAINER_TEST(container, key_type, ...)\
    {\
        typedef __VA_ARGS__ value_type;\
        EXPECT_FALSE(is_##container<bool>::value);\
        EXPECT_FALSE(is_##container<int>::value);\
        EXPECT_FALSE(is_##container<double>::value);\
        EXPECT_FALSE(is_##container<std::nullptr_t>::value);\
        EXPECT_FALSE(is_##container<std::function<void( value_type )> >::value);\
        EXPECT_FALSE(is_##container<std::stack< value_type > >::value);\
        EXPECT_FALSE(is_##container<std::queue< value_type > >::value);\
        EXPECT_FALSE(is_##container<std::priority_queue< value_type > >::value);\
        EXPECT_FALSE(is_##container<std::string>::value);\
        EXPECT_FALSE(is_##container<custrom_seq_container<value_type> >::value);\
        if(std::string("array") == #container) {EXPECT_TRUE(is_##container < std::array<value_type, 10> >::value);}\
        else { EXPECT_FALSE(is_##container < std::array<value_type, 10> >::value);}\
        if(std::string("vector") == #container) {EXPECT_TRUE(is_##container < std::vector<value_type> >::value);}\
        else { EXPECT_FALSE(is_##container < std::vector<value_type> > ::value);}\
        if(std::string("deque") == #container) {EXPECT_TRUE(is_##container < std::deque<value_type> >::value);}\
        else { EXPECT_FALSE(is_##container < std::deque<value_type> > ::value);}\
        if(std::string("forward_list") == #container) {EXPECT_TRUE(is_##container < std::forward_list<value_type> >::value);}\
        else { EXPECT_FALSE(is_##container < std::forward_list<value_type> > ::value);}\
        if(std::string("list") == #container) {EXPECT_TRUE(is_##container < std::list<value_type> >::value);}\
        else { EXPECT_FALSE(is_##container < std::list<value_type> > ::value);}\
        if(std::string("set") == #container) {\
            EXPECT_TRUE(is_##container < std::set<value_type> >::value);\
            EXPECT_TRUE(is_##container < std::multiset<key_type> >::value);\
            EXPECT_TRUE(is_##container < std::unordered_set<key_type> >::value);\
            EXPECT_TRUE(is_##container < std::unordered_multiset<key_type> >::value);\
        }else{\
            EXPECT_FALSE(is_##container < std::set<key_type> > ::value);\
            EXPECT_FALSE(is_##container < std::multiset<key_type> > ::value);\
            EXPECT_FALSE(is_##container < std::unordered_set<key_type> > ::value);\
            EXPECT_FALSE(is_##container < std::unordered_set<key_type> > ::value);\
        }\
        if(std::string("map") == #container) {\
            EXPECT_TRUE(is_##container < std::map<key_type, value_type> >::value);\
            EXPECT_TRUE(is_##container < std::multimap<key_type, value_type> >::value);\
            EXPECT_TRUE(is_##container < std::unordered_map<key_type, value_type> >::value);\
            EXPECT_TRUE(is_##container < std::unordered_multimap<key_type, value_type> >::value);\
        } else {\
            EXPECT_FALSE(is_##container < std::map<key_type, value_type> > ::value);\
            EXPECT_FALSE(is_##container < std::multimap<key_type, value_type> > ::value);\
            EXPECT_FALSE(is_##container < std::unordered_map<key_type, value_type> > ::value);\
            EXPECT_FALSE(is_##container < std::unordered_multimap<key_type, value_type> > ::value);\
        }\
    }

#endif



template<typename key_type, typename value_type = key_type>
static void test_is_deque(bool& utest_passed) {
    using namespace amo;
    EXPECT_FALSE(is_maybe_sequence_container<bool>::value);
    EXPECT_FALSE(is_maybe_sequence_container<int>::value);
    EXPECT_FALSE(is_maybe_sequence_container<double>::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::nullptr_t>::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::function<void(bool)>>::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::stack<value_type> >::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::queue<value_type> >::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::priority_queue<value_type> >::value);
    EXPECT_FALSE(is_maybe_sequence_container<std::string>::value);
    EXPECT_FALSE(is_maybe_sequence_container<custrom_seq_container<value_type> >::value);
    EXPECT_TRUE(is_maybe_sequence_container < std::array<value_type, 10>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::vector<value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::deque<value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::forward_list<value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::list<value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::set<value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::multiset<value_type> >::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::map<key_type, value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::multimap<key_type, value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::unordered_set<value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::unordered_map<key_type, value_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::unordered_multiset<key_type>>::value);
    EXPECT_FALSE(is_maybe_sequence_container < std::unordered_multimap<key_type, value_type>>::value);
}



TEST(json, is_maybe_sequence_container) {
    using namespace amo;
    test_is_maybe_sequence_containter<bool, bool>(utest_passed);
    test_is_maybe_sequence_containter<int, int>(utest_passed);
    test_is_maybe_sequence_containter<std::string, std::string>(utest_passed);
    test_is_maybe_sequence_containter<double, std::vector<int> >(utest_passed);
    test_is_maybe_sequence_containter<std::string, std::map<int, int> >(utest_passed);
}

TEST(json, is_array) {
    using namespace amo;
    AMO_TYPE_TRAITS_CONTAINER_TEST(array, bool, bool);
    AMO_TYPE_TRAITS_CONTAINER_TEST(array, int, int);
    AMO_TYPE_TRAITS_CONTAINER_TEST(array, std::string, std::string);
    AMO_TYPE_TRAITS_CONTAINER_TEST(array, std::string, std::map<int, int>);
}

TEST(json, is_vector) {
    using namespace amo;
    //AMO_TYPE_TRAITS_CONTAINER_TEST(vector, bool, bool); // bool 特化，无法验证通过
    AMO_TYPE_TRAITS_CONTAINER_TEST(vector, int, int);
    AMO_TYPE_TRAITS_CONTAINER_TEST(vector, std::string, std::string);
    AMO_TYPE_TRAITS_CONTAINER_TEST(vector, std::string, std::map<int, int>);
}

TEST(json, is_deque) {
    using namespace amo;
    typedef std::deque<int> T;
    auto a1 = is_maybe_sequence_container<T>::value;
    auto a2 = !amo::has_member_function_data<T>::value;
    auto a3 = !amo::has_member_function_capacity<T>::value;
    auto a4 = amo::has_member_function_at<T, size_t>::value;
    auto a5 = amo::has_member_function_pop_front<T>::value;
    auto a6 = amo::has_member_function_push_back<T, int>::value;
    
    auto bb =  is_deque<std::vector<int> >::value;
    auto bb1 = is_deque<custrom_seq_container<bool> >::value;
    auto bb2 = is_deque<std::deque<bool> >::value;
    AMO_TYPE_TRAITS_CONTAINER_TEST(deque, bool, bool);
    AMO_TYPE_TRAITS_CONTAINER_TEST(deque, int, int);
    AMO_TYPE_TRAITS_CONTAINER_TEST(deque, std::string, std::string);
    AMO_TYPE_TRAITS_CONTAINER_TEST(deque, std::string, std::map<int, int>);
}

TEST(json, is_forward_list) {
    using namespace amo;
    typedef std::forward_list<int> T;
    
    typedef typename amo::has_declare_iterator<T>::type iterator;
    auto a1 = is_maybe_sequence_container<T>::value;
    auto a2 = amo::has_member_function_insert_after<T, iterator, int>::value;
    
    AMO_TYPE_TRAITS_CONTAINER_TEST(forward_list, bool, bool);
    AMO_TYPE_TRAITS_CONTAINER_TEST(forward_list, int, int);
    AMO_TYPE_TRAITS_CONTAINER_TEST(forward_list, std::string, std::string);
    AMO_TYPE_TRAITS_CONTAINER_TEST(forward_list, std::string, std::map<int, int>);
}

TEST(json, is_list) {
    using namespace amo;
    AMO_TYPE_TRAITS_CONTAINER_TEST(list, bool, bool);
    AMO_TYPE_TRAITS_CONTAINER_TEST(list, int, int);
    AMO_TYPE_TRAITS_CONTAINER_TEST(list, std::string, std::string);
    AMO_TYPE_TRAITS_CONTAINER_TEST(list, std::string, std::map<int, int>);
}

TEST(json, is_set) {
    using namespace amo;
    typedef std::multiset<std::string> T;
    typedef typename amo::has_declare_key_type<T>::type key_type;
    auto a1 = is_maybe_sequence_container<T>::value;
    auto a2 = amo::has_member_function_find<T, key_type>::value;
    auto a3 = amo::has_member_function_count<T, key_type>::value;
    auto a4 = !amo::has_member_function_front<T>::value;
    auto a5 = !amo::has_declare_mapped_type<T>::value;
    
    AMO_TYPE_TRAITS_CONTAINER_TEST(set, bool, bool);
    AMO_TYPE_TRAITS_CONTAINER_TEST(set, int, int);
    AMO_TYPE_TRAITS_CONTAINER_TEST(set, std::string, std::string);
    AMO_TYPE_TRAITS_CONTAINER_TEST(set, std::string, std::map<int, int>);
}
TEST(json, is_map) {
    using namespace amo;
    typedef std::multimap<std::string, std::vector<int, int> > T;
    typedef typename amo::has_declare_key_type<T>::type key_type;
    auto a1 = is_maybe_sequence_container<T>::value;
    auto a2 = amo::has_member_function_find<T, key_type>::value;
    auto a3 = amo::has_member_function_count<T, key_type>::value;
    auto a4 = !amo::has_member_function_front<T>::value;
    auto a5 = amo::has_declare_mapped_type<T>::value;
    
    
    
    AMO_TYPE_TRAITS_CONTAINER_TEST(map, bool, bool);
    AMO_TYPE_TRAITS_CONTAINER_TEST(map, int, int);
    AMO_TYPE_TRAITS_CONTAINER_TEST(map, std::string, std::string);
    AMO_TYPE_TRAITS_CONTAINER_TEST(map, std::string, std::map<int, int>);
}



TEST(json, construct_custom_json_object_map) {
    using namespace amo;
    typedef custrom_seq_container<int> T;
    
    typedef typename amo::has_declare_value_type<T>::type value_type;
    typedef typename amo::has_declare_iterator<T>::type iterator;
    typedef typename amo::has_declare_iterator_category<iterator>::type iterator_category;
    
    auto a1 = std::is_class<T>::value;
    auto a2 = amo::has_member_function_begin<T>::value;
    auto a3 = amo::has_declare_iterator<T >::value;
    auto a4 = amo::has_declare_iterator_category<iterator>::value;
    auto a5 = !amo::has_member_function_push_back<T, value_type>::value;
    auto a6 = std::is_convertible<iterator_category, std::input_iterator_tag>::value;
    /*auto a7 = amo::has_member_function_find<T, T::key_type>::value;
    auto a8 = amo::has_member_function_count<T, size_t>::value;*/
    auto a9 = !amo::has_member_function_front<T>::value;
    auto a10 = amo::has_declare_mapped_type<T>::value;
    
}

TEST(json, construct_custom_json_object0) {
    using namespace amo;
    std::cout << "------------------" << std::endl;
    typedef std::list<int> T;
    typedef typename amo::has_declare_value_type<T>::type value_type;
    typedef typename amo::has_declare_iterator<T>::type iterator;
    typedef typename amo::has_declare_iterator_category<iterator>::type iterator_category;
    auto a1 = std::is_class<T>::value;
    auto a2 = amo::has_member_function_begin<T>::value;
    auto a3 = amo::has_declare_iterator<T >::value;
    auto a4 = amo::has_declare_iterator_category<iterator>::value;
    auto a5 = amo::has_member_function_push_back<T, value_type>::value;
    auto a6 = std::is_convertible<iterator_category, std::input_iterator_tag>::value;
    
    std::cout << is_maybe_sequence_container<std::vector<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::list<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::deque<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::array<int, 10>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::forward_list<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::set<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::queue<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::map<int, int>>::value << std::endl;
    std::cout << is_map<std::queue<int>>::value << std::endl;
    std::cout << is_map<std::map<int, double>>::value << std::endl;
    std::cout << "------------------" << std::endl;
}

TEST(json, construct_custom_json_object1) {
    using namespace amo;
    std::cout << "------------------" << std::endl;
    typedef std::forward_list<int> T;
    typedef typename amo::has_declare_iterator<T>::type iterator;
    typedef typename amo::has_declare_iterator_category<iterator>::type iterator_category;
    auto a1 = std::is_class<T>::value;
    auto a2 = amo::has_member_function_begin<T>::value;
    auto a3 = amo::has_declare_iterator<T >::value;
    auto a4 = amo::has_declare_iterator_category<iterator>::value;
    auto a5 = std::is_convertible<iterator_category, std::input_iterator_tag>::value;
    
    std::cout << is_maybe_sequence_container<std::vector<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::list<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::deque<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::array<int, 10>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::forward_list<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::set<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::queue<int>>::value << std::endl;
    std::cout << "------------------" << std::endl;
}

TEST(json, construct_custom_json_object2) {
    using namespace amo;
    std::cout << "------------------" << std::endl;
    std::cout << is_maybe_sequence_container<std::vector<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::list<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::deque<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::array<int, 10>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::forward_list<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::set<int>>::value << std::endl;
    std::cout << is_maybe_sequence_container<std::queue<int>>::value << std::endl;
    std::cout << "------------------" << std::endl;
}

TEST(json, construct_custom_json_object3) {
    using namespace amo;
    std::cout << "------------------" << std::endl;
    std::cout << amo::has_member_function_push_back<std::vector<int>>::value << std::endl;
    std::cout << is_array<std::vector<int>>::value << std::endl;
    std::cout << is_array<std::string>::value << std::endl;
    std::cout << is_array<std::list<int>>::value << std::endl;
    std::cout << is_array<std::deque<int>>::value << std::endl;
    std::cout << is_array<std::array<int, 10>>::value << std::endl;
    std::cout << is_array<std::forward_list<int>>::value << std::endl;
    std::cout << is_array<std::set<int>>::value << std::endl;
    std::cout << is_array<std::queue<int>>::value << std::endl;
    std::cout << "------------------" << std::endl;
}

TEST(json, construct_custom_json_object4) {
    using namespace amo;
    std::cout << "------------------" << std::endl;
    std::cout << amo::has_member_function_push_back<std::vector<int>>::value << std::endl;
    std::cout << is_vector<std::vector<int>>::value << std::endl;
    std::cout << is_vector<std::string>::value << std::endl;
    std::cout << is_vector<std::list<int>>::value << std::endl;
    std::cout << is_vector<std::deque<int>>::value << std::endl;
    std::cout << is_vector<std::array<int, 10>>::value << std::endl;
    std::cout << is_vector<std::forward_list<int>>::value << std::endl;
    std::cout << is_vector<std::set<int>>::value << std::endl;
    std::cout << is_vector<std::queue<int>>::value << std::endl;
    std::cout << "------------------" << std::endl;
}

TEST(json, construct_custom_json_object) {

    json_type json;
    json.set_object();
    json["m_str"] = "test str";
    
    amo::custom_class3 custom1 = json;
    amo::custom_class3* custom2 = json;
    std::shared_ptr<amo::custom_class3> custom3 = json;
    amo::custom_class3* custom4;
    custom4 = json;
    
    delete custom2;
    
    json_type arr{ 31, 32, 33, 34, 35, 36, 37, 38, 39 };
    char c5[10] = { 0 };
    amo::single_object_get_set_helper<amo::json_type_upgrader<decltype(c5)>, json_type >().get(arr, c5);
    std::vector<char> vec = arr;
    std::cout << typeid(std::vector<char>::iterator::iterator_category).name() << std::endl;
    std::cout << std::is_convertible< std::random_access_iterator_tag, std::bidirectional_iterator_tag>::value << std::endl;
    std::cout << std::is_convertible< std::bidirectional_iterator_tag, std::bidirectional_iterator_tag>::value << std::endl;
    std::cout << std::is_base_of< std::random_access_iterator_tag, std::bidirectional_iterator_tag>::value << std::endl;
    std::cout << std::is_base_of< std::bidirectional_iterator_tag, std::random_access_iterator_tag>::value << std::endl;
    
    typedef std::vector<char> T;
    std::cout << amo::has_declare_iterator<T>::value << std::endl;
    std::cout << amo::has_declare_iterator_category<amo::has_declare_iterator<T>::type>::value << std::endl;
    std::cout << std::is_convertible
              < amo::has_declare_iterator_category<amo::has_declare_iterator<T>::type>::type, std::bidirectional_iterator_tag >::value
              << std::endl;
              
              
    //std::array<char, 10> a = arr;
    /*char c5[6] =  json;
    char c6[6] = { 1,2,3,4 };
    c6 = json;*/
}

TEST(json, get_error_msg) {
    // error json
    json_type json14 = amo::string_reader("{ \"aaa\":3a, \"bbb\":\"3.0\", \"ccc\":true,\"ddd\":null }");
    
    EXPECT_EQ(json14.is_valid(), false);
    std::cout << json14.get_error_msg() << std::endl;
    json_type json15(amo::string_reader{ "111 a" });
    EXPECT_EQ(json15.is_valid(), false);
    std::cout << json15.get_error_msg() << std::endl;
    
}

TEST(json, construct_with_std_array) {
    int* a{};
    std::array<int, 10> arr = { 1, 2 };
    json_type json = arr;
    std::cout << json.to_string() << std::endl;
    std::array<int, 10> arr2 = json;
    json.push_back({ 5, 6, 7, 9 });
    std::array<int, 10> arr3 = json;
    arr3 = json;
}

TEST(json, construct_with_vector) {
    typedef std::vector<int> VecterType1;
    VecterType1 data{ 1, 2, 3, 4, 5, 6 };
    
    json_type json = data;
    VecterType1 vec = json;
    vec = json.operator VecterType1();
    vec = json.get<VecterType1 >();
    //vec = json;  // 不支持,operator=不明确
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
    EXPECT_EQ(vec[5], 6);
    
    std::shared_ptr<VecterType1> smart_vec = json;
    VecterType1* ptr_vec = json;
    delete ptr_vec;
    typedef   std::vector<VecterType1> VectorType2;
    VectorType2 data2{ data, data };
    json_type json2 = data2;
    std::cout << json2.to_string() << std::endl;
    json2 = data2;
    VectorType2 vec2 = json2;
    VecterType1 vec3 = json2;
    std::shared_ptr< VectorType2> smart_vec2 = json2;
    VectorType2* ptr_vec2 = json2;
    ptr_vec2 = json2;
    
}

TEST(json, construct_with_deque) {
    typedef std::deque<int> ContainerType;
    ContainerType data{0, 1, 2, 3, 4, 5, 6 };
    json_type arr = data;
    ContainerType vec = arr;
    //vec = arr; //operator=不明确的情况下会编译报错，所有的标准库容器都不行
    ContainerType* ptr = arr;
    std::shared_ptr<ContainerType> smart = arr;
    delete ptr;
    arr.push_back({ 7, 8, 9, 10 });
    ptr = arr;
    smart = arr;
}

TEST(json, construct_with_forward_list) {
    typedef std::forward_list<int> ContainerType;
    ContainerType data{ 0, 1, 2, 3, 4, 5, 6 };
    json_type arr = data;
    std::cout << arr.to_string() << std::endl;
    ContainerType vec = arr;
    //vec = arr; //operator=不明确的情况下会编译报错，所有的标准库容器都不行
    ContainerType* ptr = arr;
    std::shared_ptr<ContainerType> smart = arr;
    delete ptr;
    arr.push_back({ 7, 8, 9, 10 });
    ptr = arr;
    smart = arr;
}

TEST(json, construct_with_list) {
    typedef std::forward_list<int> ContainerType;
    ContainerType data{ 0, 1, 2, 3, 4, 5, 6 };
    json_type arr = data;
    std::cout << arr.to_string() << std::endl;
    ContainerType vec = arr;
    //vec = arr; //operator=不明确的情况下会编译报错，所有的标准库容器都不行
    ContainerType* ptr = arr;
    std::shared_ptr<ContainerType> smart = arr;
    delete ptr;
    arr.push_back({ 7, 8, 9, 10 });
    ptr = arr;
    smart = arr;
}

TEST(json, construct_with_set) {
    typedef std::set<int> ContainerType;
    ContainerType data{ 0, 1, 2, 3, 4, 5, 6 };
    json_type arr = data;
    std::cout << arr.to_string() << std::endl;
    ContainerType vec = arr;
    //vec = arr; //operator=不明确的情况下会编译报错，所有的标准库容器都不行
    ContainerType* ptr = arr;
    std::shared_ptr<ContainerType> smart = arr;
    delete ptr;
    arr.push_back({ 7, 8, 9, 10 });
    ptr = arr;
    smart = arr;
}


TEST(json, construct_with_map) {
    typedef std::map<std::string, int> ContainerType;
    ContainerType data{ {"0", 0}, {"1", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6} };
    json_type arr = data;
    std::cout << arr.to_string() << std::endl;
    ContainerType vec = arr;
    //vec = arr; //operator=不明确的情况下会编译报错，所有的标准库容器都不行
    ContainerType* ptr = arr;
    std::shared_ptr<ContainerType> smart = arr;
    delete ptr;
    arr["7"] = 7;
    arr["8"] = 8;
    arr["9"] = 9;
    arr["10"] = 10;
    ptr = arr;
    smart = arr;
    delete ptr;
}

TEST(json, construct_with_map2) {
    typedef std::map<int, int> ContainerType;
    ContainerType data{ {0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6} };
    json_type arr = data;
    std::cout << arr.to_string() << std::endl;
    ContainerType vec = arr;
    //vec = arr; //operator=不明确的情况下会编译报错，所有的标准库容器都不行
    ContainerType* ptr = arr;
    std::shared_ptr<ContainerType> smart = arr;
    delete ptr;
    arr.push_back({ 7, 8, 9, 10 });  // 插入非法的键值对
    ptr = arr; // nullptr
    smart = arr; // nullptr
}


TEST(json, construct_with_ptr) {
    amo::custom_class* custom_ptr = new amo::custom_class("123");
    std::cout << json_type(custom_ptr).to_string() << std::endl;
    delete custom_ptr;
    custom_ptr = nullptr;
    EXPECT_EQ(json_type(custom_ptr).is_empty(), true);
    
    int* int_ptr = new int(3);
    EXPECT_EQ(json_type(int_ptr), 3);
    double* float_ptr = new double(3.2212);
    EXPECT_EQ(json_type(float_ptr), 3.2212);
    std::string* str_ptr = new std::string("abcdef");
    EXPECT_EQ(json_type(str_ptr), std::string("abcdef"));
    EXPECT_TRUE(json_type(str_ptr) == "abcdef");
    EXPECT_TRUE(json_type(str_ptr) == json_type(str_ptr));
}

TEST(json, construct_with_shared_ptr) {
    std::shared_ptr< amo::custom_class> custom_ptr(new amo::custom_class("123"));
    std::cout << json_type(custom_ptr).to_string() << std::endl;
    
    custom_ptr.reset();
    EXPECT_EQ(json_type(custom_ptr).is_empty(), true);
    
    std::shared_ptr < int> int_ptr(new int(3));
    EXPECT_EQ(json_type(int_ptr), 3);
    std::shared_ptr <  double>float_ptr(new double(3.2212));
    EXPECT_EQ(json_type(float_ptr), 3.2212);
    std::shared_ptr<std::string> str_ptr(new std::string("abcdef"));
    EXPECT_EQ(json_type(str_ptr), std::string("abcdef"));
    EXPECT_TRUE(json_type(str_ptr) == "abcdef");
    EXPECT_TRUE(json_type(str_ptr) == json_type(str_ptr));
}

TEST(json, construct_with_unique_ptr) {
    std::unique_ptr< amo::custom_class> custom_ptr(new amo::custom_class("123"));
    std::cout << json_type(custom_ptr).to_string() << std::endl;
    
    custom_ptr.reset();
    std::unique_ptr< amo::custom_class> custom_ptr2 = json_type(custom_ptr);
    EXPECT_EQ(json_type(custom_ptr).is_empty(), true);
    
    std::unique_ptr < int> int_ptr(new int(3));
    EXPECT_EQ(json_type(int_ptr), 3);
    std::unique_ptr <  double>float_ptr(new double(3.2212));
    EXPECT_EQ(json_type(float_ptr), 3.2212);
    std::unique_ptr<std::string> str_ptr(new std::string("abcdef"));
    EXPECT_EQ(json_type(str_ptr), std::string("abcdef"));
    EXPECT_TRUE(json_type(str_ptr) == "abcdef");
    EXPECT_TRUE(json_type(str_ptr) == json_type(str_ptr));
}



