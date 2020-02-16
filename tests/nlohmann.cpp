#include <iostream>
#include <fstream>

#include "./../json.hpp"
#include "./utest.hpp"

#include "nlohmann/json.hpp"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

namespace {

    int32_t length = 10000;
    nlohmann::json make_json() {
        nlohmann::json vec1;
        vec1.push_back("1");
        vec1.push_back("2");
        vec1.push_back("3");
        
        nlohmann::json vec2;
        vec2.push_back(4);
        vec2.push_back(5);
        vec2.push_back(6);
        
        nlohmann::json vec3;
        
        {
            nlohmann::json arr3;
            arr3.push_back(7);
            arr3.push_back(8);
            arr3.push_back(9);
            
            vec3.push_back(arr3);
            vec3.push_back(arr3);
            vec3.push_back(arr3);
        }
        
        
        nlohmann::json json;
        json  ["vec1"] = (vec1);
        json  ["vec2"] = (vec2);
        json  ["vec3"] = (vec3);
        
        
        nlohmann::json info;
        info["m_bool"] = (true);
        //info=["m_char", 'c');
        info["m_int8_t"] = (8);
        info["m_int16_t"] = (16);
        info["m_int32_t"] = (32);
        info["m_int64_t"] = (64);
        info["m_uint8_t"] = (8);
        info["m_uint16_t"] = (16);
        info["m_uint32_t"] = (32);
        info["m_uin64_t"] = (64);
        info["m_float"] = (1.0);
        info["m_double"] = (2.22);
        info["m_string"] = ("string txt");
        
        json  ["m_jsoninfo2"] = (info);
        json  ["m_jsoninfo3"] = (info);
        
        
        nlohmann::json jsoninfoclass;
        jsoninfoclass  ["m_jsoninfo1"] = (info);
        jsoninfoclass  ["m_jsoninfo2"] = (info);
        
        json  ["m_jsoninfo2"] = (jsoninfoclass);
        json  ["m_jsoninfo3"] = (jsoninfoclass);
        
        nlohmann::json arr;
        arr.push_back(jsoninfoclass);
        arr.push_back(jsoninfoclass);
        arr.push_back(jsoninfoclass);
        arr.push_back(jsoninfoclass);
        
        json  ["m_jsoninfo4"] = (arr);
        json  ["m_jsoninfo5"] = (arr);
        
        nlohmann::json arr2;
        arr2.push_back(arr);
        arr2.push_back(arr);
        arr2.push_back(arr);
        json  ["m_jsoninfo6"] = (arr2);
        
        return json;
    }
}


namespace ns {
    // a simple struct to model a person
    struct person {
        std::string name;
        std::string address;
        int age;
    };
}

using nlohmann::json;

namespace ns {
    void to_json(json& j, const person& p) {
        j = json{ {"name", p.name}, {"address", p.address}, {"age", p.age} };
    }
    
    void from_json(const json& j, person& p) {
        /* j.at("name").get_to(p.name);
         j.at("address").get_to(p.address);
         j.at("age").get_to(p.age);*/
    }
} // namespace ns

#include <random>

 

TEST(nlohmann, construct_double) {
    typedef double value_type;
    std::random_device rng;
    
    value_type m_min = (std::numeric_limits<value_type>::min)();
    value_type m_max = (std::numeric_limits<value_type>::max)();
    std::uniform_real_distribution<value_type> gen(m_min, m_max);
    
    std::vector<value_type> vec = { m_min, m_max, 9007199254740992, 9007199254740991, -9007199254740991, -9007199254740992 };
    
    // ±ß½ç
    for (size_t i = 0; i < vec.size(); ++i) {
    
        EXPECT_EQ(nlohmann::json(i), i);
        EXPECT_EQ(nlohmann::json::parse(std::to_string(i)), i);
    }
    
    
    for (size_t index = 0; index < 100000; ++index) {
        value_type i = gen(rng);
        //EXPECT_EQ(nlohmann::json(i), i);
        
        /* if (json_type(amo::string_reader{ std::to_string(i) }) != i) {
             std::cout << std::to_string(i) << std::endl;
             std::cout << i << std::endl;
         }*/
        double b = nlohmann::json::parse({ std::to_string(i) });
        double bc = fabs(1.0 - b / i);
        EXPECT_TRUE(fabs(1.0 - b / i) < 1e-16);
        //EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
}

TEST(nlohmann_pfms, to_string666) {

    auto j = nlohmann::json::parse("25693474047343731222971916836204724031989841227541403449939434236654982714790646739048977830163160673244981712509294469909782455294141905106209854313233757363237270984566803565251607417443553784851913506518558360767111231868078549587328028877260849534595394273221754633538885668292143245571908625160772517888.000000");
    double b = j.get<double>();
    std::string sb = std::to_string(b);
    double d = 2.5693474047343731e+307;
    nlohmann::json json = make_json();
    std::size_t size = 0;
    
    for (int32_t i = 0; i < length; ++i) {
        size += json.dump(0).size();
    }
    
    std::cout << size << std::endl;
}



TEST(nlohmann_pfms, data_txt) {
    std::ifstream ifs("./data/data.txt");
    
    while (ifs.is_open() && !ifs.eof()) {
        char buffer[1024] = { 0 };
        ifs.getline(buffer, 1024);
        
        if (ifs.gcount() <= 0) {
            continue;
        }
        
        std::string filename = "./data/";
        filename += buffer;
        nlohmann::json json;
        ifs >> json;
    }
}

TEST(nlohmann_pfms, canada) {
    for (int i = 0; i < 100; ++i) {
        std::string filename = "./data/nativejson-benchmark/canada.json";
        std::ifstream ifs(filename, std::ios::in | std::ios::binary);
        nlohmann::json j;
        ifs >> j;
    }
}
TEST(nlohmann_pfms, citm_catalog) {
    for (int i = 0; i < 100; ++i) {
        std::string filename = "./data/nativejson-benchmark/citm_catalog.json";
        std::ifstream ifs(filename, std::ios::in | std::ios::binary);
        nlohmann::json j;
        ifs >> j;
    }
}

TEST(nlohmann_pfms, twitter) {
    for (int i = 0; i < 100; ++i) {
        std::string filename = "./data/nativejson-benchmark/twitter.json";
        std::ifstream ifs(filename, std::ios::in | std::ios::binary);
        nlohmann::json j;
        ifs >> j;
    }
}

TEST(nlohmann_pfms, to_file) {
    nlohmann::json json1 = make_json();
    nlohmann::json arr;
    
    for (int i = 0; i < length; ++i) {
        arr.push_back(json1);
    }
    
    std::fstream ofs("./bigstr.json", std::ios::out | std::ios::binary);
    ofs << arr;
}

TEST(nlohmann_pfms, to_string) {
    nlohmann::json json = make_json();
    std::size_t size = 0;
    
    for (int32_t i = 0; i < length; ++i) {
        size += json.dump().size();
    }
    
    std::cout << size << std::endl;
}

TEST(nlohmann_pfms, to_string1) {
    nlohmann::json json = make_json();
    std::size_t size = 0;
    
    for (int32_t i = 0; i < length; ++i) {
        size += json.dump(4).size();
    }
    
    std::cout << size << std::endl;
}

TEST(nlohmann_pfms, from_string) {
    nlohmann::json json = make_json();
    std::string str = json.dump();
    uint32_t size = 0;
    
    for (int32_t i = 0; i < length; ++i) {
        size = nlohmann::json::parse(str).size();
    }
    
    std::cout << size << std::endl;
}

TEST(nlohmann_pfms, from_file) {
    std::string filename = "./bigstr.json";
    std::ifstream ifs(filename, std::ios::in | std::ios::binary);
    nlohmann::json j;
    ifs >> j;
}


TEST(nlohmann_pfms, array_test) {
    nlohmann::json json1;
    
    for (int i = 0; i < length * 10; ++i) {
        json1.push_back(555);
    }
    
    for (int i = 0; i < length * 10; ++i) {
        json1[i] = (i);
    }
}
