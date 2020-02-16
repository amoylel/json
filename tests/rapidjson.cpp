#include <iostream>
#include <fstream>

#include "./utest.hpp"

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


namespace {

    int32_t length = 10000;
    
    
    std::string rapidjsonToString(const rapidjson::Document& json) {
        std::stringstream ss;
        rapidjson::OStreamWrapper osw(ss);
        rapidjson::Writer< rapidjson::OStreamWrapper> writer(osw);
        json.Accept(writer);
        return ss.str();
    }
    
    
    template<typename T>  void putPod(rapidjson::Document& doc, const std::string& key, const T& val) {
        rapidjson::Value node;
        node = val;
        
        rapidjson::Value name;
        name.SetString(key.c_str(), doc.GetAllocator());
        doc.AddMember(name, node, doc.GetAllocator());
    }
    
    void putValue(rapidjson::Document& doc, const std::string& key, const rapidjson::Value& val) {
        rapidjson::Value name;
        name.SetString(key.c_str(), doc.GetAllocator());
        doc.AddMember(name, rapidjson::Value().CopyFrom(val,
                      doc.GetAllocator()), doc.GetAllocator());
        return;
        
    }
    
    void pushBack(rapidjson::Document& doc,  const rapidjson::Value& val) {
        rapidjson::Value v;
        v.CopyFrom(val, doc.GetAllocator());
        doc.PushBack(v, doc.GetAllocator());
    }
    
    rapidjson::Document make_json2() {
        rapidjson::Document info;
        info.SetObject();
        
        putPod(info, "m_bool", true);
        putPod(info, "m_int8_t", 8);
        putPod(info, "m_int16_t", 16);
        putPod(info, "m_int32_t", 32);
        putPod(info, "m_int64_t", 64);
        putPod(info, "m_uint8_t", 8);
        putPod(info, "m_uint16_t", 16);
        putPod(info, "m_uint32_t", 32);
        putPod(info, "m_uin64_t", 64);
        putPod(info, "m_float", 1.0);
        putPod(info, "m_double", 2.22);
        
        {
            rapidjson::Value name;
            name.SetString("m_string", info.GetAllocator());
            rapidjson::Value node;
            node.SetString("string txt", info.GetAllocator());
            info.AddMember(name, node, info.GetAllocator());
        }
        
        {
            rapidjson::Value name;
            name.SetString("m_string2", info.GetAllocator());
            rapidjson::Value node;
            node.SetString(u8"string txt中文件目录", info.GetAllocator());
            info.AddMember(name, node, info.GetAllocator());
        }
        {
            rapidjson::Value name;
            name.SetString("m_string3", info.GetAllocator());
            rapidjson::Value node;
            node.SetString("string txt中文", info.GetAllocator());
            info.AddMember(name, node, info.GetAllocator());
        }
        
        {
        
            std::string sb = "\u8fd9\u4e00\u5468\uff1a\u8d2b\u7a77\u66b4\u51fb";
            rapidjson::Value name;
            name.SetString("m_string4", info.GetAllocator());
            rapidjson::Value node;
            node.SetString("\u8fd9\u4e00\u5468\uff1a\u8d2b\u7a77\u66b4\u51fb", info.GetAllocator());
            info.AddMember(name, node, info.GetAllocator());
        }
        
        {
        
            std::string sb = "\b\t\r\n\f\\\"";
            rapidjson::Value name;
            name.SetString("m_string5", info.GetAllocator());
            rapidjson::Value node;
            node.SetString(sb.c_str(), info.GetAllocator());
            info.AddMember(name, node, info.GetAllocator());
        }
        
        return info;
    }
    
    rapidjson::Document make_json() {
        rapidjson::Document vec1;
        vec1.SetArray();
        
        {
            rapidjson::Value v;
            v.SetString("1", vec1.GetAllocator());
            vec1.PushBack(v, vec1.GetAllocator());
        }
        {
            rapidjson::Value v;
            v.SetString("2", vec1.GetAllocator());
            vec1.PushBack(v, vec1.GetAllocator());
        }
        {
            rapidjson::Value v;
            v.SetString("3", vec1.GetAllocator());
            vec1.PushBack(v, vec1.GetAllocator());
        }
        
        
        
        rapidjson::Document vec2;
        vec2.SetArray();
        {
            rapidjson::Value v;
            v.SetInt(4);
            vec2.PushBack(v, vec2.GetAllocator());
        }
        {
            rapidjson::Value v;
            v.SetInt(5);
            vec2.PushBack(v, vec2.GetAllocator());
        }
        {
            rapidjson::Value v;
            v.SetInt(6);
            vec2.PushBack(v, vec2.GetAllocator());
        }
        
        
        
        
        rapidjson::Document vec3;
        vec3.SetArray();
        {
            rapidjson::Document arr3;
            arr3.SetArray();
            {
                rapidjson::Value v;
                v.SetInt(7);
                arr3.PushBack(v, arr3.GetAllocator());
            }
            {
                rapidjson::Value v;
                v.SetInt(8);
                arr3.PushBack(v, arr3.GetAllocator());
            }
            {
                rapidjson::Value v;
                v.SetInt(9);
                arr3.PushBack(v, arr3.GetAllocator());
            }
            
            for (int i = 0; i < 3; ++i) {
                rapidjson::Value v;
                v.CopyFrom(arr3, vec3.GetAllocator());
                vec3.PushBack(v, vec3.GetAllocator());
            }
        }
        
        
        rapidjson::Document json;
        json.SetObject();
        
        {
            rapidjson::Value name;
            name.SetString("vec1", json.GetAllocator());
            json.AddMember(name, rapidjson::Value().CopyFrom(vec1, json.GetAllocator()), json.GetAllocator());
        }
        
        {
            rapidjson::Value name;
            name.SetString("vec2", json.GetAllocator());
            json.AddMember(name, rapidjson::Value().CopyFrom(vec2, json.GetAllocator()), json.GetAllocator());
        }
        
        {
            rapidjson::Value name;
            name.SetString("vec3", json.GetAllocator());
            json.AddMember(name, rapidjson::Value().CopyFrom(vec3, json.GetAllocator()), json.GetAllocator());
        }
        
        
        
        rapidjson::Document info;
        info.SetObject();
        
        putPod(info, "m_bool", true);
        putPod(info, "m_int8_t", 8);
        putPod(info, "m_int16_t", 16);
        putPod(info, "m_int32_t", 32);
        putPod(info, "m_int64_t", 64);
        putPod(info, "m_uint8_t", 8);
        putPod(info, "m_uint16_t", 16);
        putPod(info, "m_uint32_t", 32);
        putPod(info, "m_uin64_t", 64);
        putPod(info, "m_float", 1.0);
        putPod(info, "m_double", 2.22);
        
        {
            rapidjson::Value name;
            name.SetString("m_string", vec2.GetAllocator());
            rapidjson::Value node;
            node.SetString("string txt", vec2.GetAllocator());
            info.AddMember(name, node, info.GetAllocator());
            //node.GetString();
        }
        
        
        
        // rapidjson 不能使键值唯一
        putValue(json, "m_jsoninfo2", info);
        putValue(json, "m_jsoninfo3", info);
        // std::cout << rapidjsonToString(json) << std::endl;
        
        rapidjson::Document jsoninfoclass;
        jsoninfoclass.SetObject();
        
        putValue(jsoninfoclass, "m_jsoninfo1", info);
        putValue(jsoninfoclass, "m_jsoninfo2", info);
        
        putValue(json, "m_jsoninfo2", jsoninfoclass);
        putValue(json, "m_jsoninfo3", jsoninfoclass);
        
        //	std::cout << rapidjsonToString(json) << std::endl;
        rapidjson::Document arr;
        arr.SetArray();
        pushBack(arr, jsoninfoclass);
        pushBack(arr, jsoninfoclass);
        pushBack(arr, jsoninfoclass);
        pushBack(arr, jsoninfoclass);
        
        putValue(json, "m_jsoninfo4", arr);
        putValue(json, "m_jsoninfo5", arr);
        
        rapidjson::Document arr2;
        arr2.SetArray();
        pushBack(arr2, arr);
        pushBack(arr2, arr);
        pushBack(arr2, arr);
        
        putValue(json, "m_jsoninfo6", arr2);
        
        return json;
    }
}
TEST(rapidjson_pfms, test331321) {

    rapidjson::Document doc;
    doc.Parse("5708990770823839207320493820740630171355185151999e-3");
    double dbm = doc.GetFloat();
    std::cout << dbm << std::endl;
}


#include <random>
TEST(rapidjson_pfms, construct_double) {
    typedef double value_type;
    std::random_device rng;
    
    value_type m_min = (std::numeric_limits<value_type>::min)();
    value_type m_max = (std::numeric_limits<value_type>::max)();
    std::uniform_real_distribution<value_type> gen(m_min, m_max);
    
    std::vector<value_type> vec = { m_min, m_max, 9007199254740992, 9007199254740991, -9007199254740991, -9007199254740992 };
    
    // 边界
    
    
    for (size_t index = 0; index < 100000; ++index) {
        value_type i = gen(rng);
        std::string str = std::to_string(i);
        rapidjson::Document doc;
        doc.Parse(str.c_str());
        
        
        /* if (json_type(amo::string_reader{ std::to_string(i) }) != i) {
             std::cout << std::to_string(i) << std::endl;
             std::cout << i << std::endl;
         }*/
        double b = doc.GetDouble();
        double bc = fabs(1.0 - b / i);
        EXPECT_TRUE(fabs(1.0 - b / i) < 1e-14);
        //EXPECT_EQ(json_type(amo::string_reader{ std::to_string(i) }), i);
    }
}

TEST(rapidjson_pfms, data_txt) {
    std::ifstream ifs("./data/data.txt");
    
    while (ifs.is_open() && !ifs.eof()) {
        char buffer[1024] = { 0 };
        ifs.getline(buffer, 1024);
        
        if (ifs.gcount() <= 0) {
            continue;
        }
        
        std::string filename = "./data/";
        filename += buffer;
        std::ifstream ifs2(filename, std::ios::in | std::ios::binary);
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::IStreamWrapper isw(ifs2);
        doc.ParseStream(isw);
    }
    
}

TEST(rapidjson_pfms, canada0) {
    size_t index = 0;
    
    for (int i = 0; i < 100; ++i) {
        std::string filename = "./data/nativejson-benchmark/canada.json";
        std::ifstream ifs(filename, std::ios::in | std::ios::binary);
        std::ifstream* stream_ = &ifs;
        char buffer[1024 * 10 + 1] = { 0 };  // 临时缓存
        std::string str;
        // 读取stream_中的所有数据到str中
        while (stream_->good()) {
            stream_->read(buffer, 1024 * 10);
            str.append(buffer, (size_t)stream_->gcount());
        }
        
        str += '\0';
        index += str.size();
        //json_type json = amo::file_reader{ filename };
    }
    std::cout << index << std::endl;
    
}
TEST(rapidjson_pfms, canada_1) {

    std::string filename = "./data/nativejson-benchmark/canada.json";
    std::ifstream ifs(filename, std::ios::in | std::ios::binary);
    std::ifstream* stream_ = &ifs;
    char buffer[1024 * 10 + 1] = { 0 };  // 临时缓存
    std::string str;
    // 读取stream_中的所有数据到str中
    while (stream_->good()) {
        stream_->read(buffer, 1024 * 10);
        str.append(buffer, (size_t)stream_->gcount());
    }
    
    str += '\0';
    for (int i = 0; i < 100; ++i) {
        rapidjson::Document doc;
        doc.SetObject();
        doc.Parse(str.c_str());
    }
    
}
TEST(rapidjson_pfms, canada) {

    for (int i = 0; i < 100; ++i) {
        std::string filename = "./data/nativejson-benchmark/canada.json";
        std::ifstream ifs(filename, std::ios::in | std::ios::binary);
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::IStreamWrapper isw(ifs);
        doc.ParseStream(isw);
    }
}

TEST(rapidjson_pfms, citm_catalog) {

    for (int i = 0; i < 100; ++i) {
        std::string filename = "./data/nativejson-benchmark/citm_catalog.json";
        std::ifstream ifs(filename, std::ios::in | std::ios::binary);
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::IStreamWrapper isw(ifs);
        doc.ParseStream(isw);
    }
}


TEST(rapidjson_pfms, twitter_1) {

    std::string filename = "./data/nativejson-benchmark/twitter.json";
    std::ifstream ifs(filename, std::ios::in | std::ios::binary);
    std::ifstream* stream_ = &ifs;
    char buffer[1024 * 10 + 1] = { 0 };  // 临时缓存
    std::string str;
    // 读取stream_中的所有数据到str中
    while (stream_->good()) {
        stream_->read(buffer, 1024 * 10);
        str.append(buffer, (size_t)stream_->gcount());
    }
    
    str += '\0';
    for (int i = 0; i < 100; ++i) {
        rapidjson::Document doc;
        doc.SetObject();
        doc.Parse(str.c_str());
    }
    
}
TEST(rapidjson_pfms, twitter) {

    for (int i = 0; i < 100; ++i) {
        std::string filename = "./data/nativejson-benchmark/twitter.json";
        std::ifstream ifs(filename, std::ios::in | std::ios::binary);
        rapidjson::Document doc;
        doc.SetObject();
        rapidjson::IStreamWrapper isw(ifs);
        doc.ParseStream(isw);
    }
}

TEST(rapidjson_pfms, to_file) {

    rapidjson::Document json1 = make_json();
    rapidjson::Document arr;
    arr.SetArray();
    
    for (int i = 0; i < length * 1  ; ++i) {
        pushBack(arr, json1);
    }
    
    std::ofstream ofs("./bigstr.json", std::ios::out | std::ios::binary);
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    arr.Accept(writer);
    
    
}

TEST(rapidjson_pfms, from_file) {
    std::string filename = "./bigstr.json";
    std::ifstream ifs(filename, std::ios::in | std::ios::binary);
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::IStreamWrapper isw(ifs);
    doc.ParseStream(isw);
}

static std::string ssss111;
TEST(rapidjson_pfms, from_file3) {
    std::ifstream ifs("./bigstr.json", std::ios::in | std::ios::binary);
    std::string str;
    const int len = 65535;
    char buffer[len] = { 0 };
    
    while (!ifs.eof()) {
        ifs.read(buffer, len);
        int gcount = ifs.gcount();
        
        str += std::string(buffer, gcount);
    }
    
    ssss111 = str;
    std::cout << str.size() << std::endl;
    
}

TEST(rapidjson_pfms, from_file4) {
    rapidjson::Document doc;
    doc.Parse(ssss111.c_str());
}
TEST(rapidjson_pfms, to_string) {
    rapidjson::Document json = make_json();
    std::size_t size = 0;
    
    for (int32_t i = 0; i < length; ++i) {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        json.Accept(writer);
        size += buffer.GetSize();
    }
    
    std::cout << size << std::endl;
}

TEST(rapidjson_pfms, from_string) {
    rapidjson::Document json = make_json();
    
    std::stringstream ss;
    rapidjson::OStreamWrapper osw(ss);
    rapidjson::Writer< rapidjson::OStreamWrapper> writer(osw);
    json.Accept(writer);
    std::string str = ss.str();
    
    std::size_t size = 0;
    
    
    for (int32_t i = 0; i < length; ++i) {
        rapidjson::Document doc;
        doc.Parse(str.c_str());
        
        
        /*   std::stringstream ss2(str);
           rapidjson::IStreamWrapper isw(ss2);
           doc.ParseStream(isw);
           */
        size += (str).size();
    }
    
    std::cout << size << std::endl;
}

TEST(rapidjson_pfms, from_string2) {
    rapidjson::Document json = make_json2();
    
    std::stringstream ss;
    rapidjson::OStreamWrapper osw(ss);
    rapidjson::Writer< rapidjson::OStreamWrapper> writer(osw);
    json.Accept(writer);
    std::string str = ss.str();
    
    std::size_t size = 0;
    
    
    for (int32_t i = 0; i < length; ++i) {
        rapidjson::Document doc;
        doc.Parse(str.c_str());
        
        
        /*   std::stringstream ss2(str);
        rapidjson::IStreamWrapper isw(ss2);
        doc.ParseStream(isw);
        */
        size += (str).size();
    }
    
    std::cout << size << std::endl;
}
TEST(rapidjson_pfms, bool_object_test) {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Value v;
    v.SetBool(false);
    
    for (int i = 0; i < length * 2; ++i) {
        rapidjson::Value name;
        name.SetString(std::to_string(i).c_str(), doc.GetAllocator());
        rapidjson::Value node;
        node.CopyFrom(v, doc.GetAllocator());
        doc.AddMember(name,  node, doc.GetAllocator());
    }
    
    for (int i = 0; i < length * 2; ++i) {
        rapidjson::Value name;
        name.SetString(std::to_string(i).c_str(), doc.GetAllocator());
        auto iter = doc.FindMember(name);
        iter->value.SetBool(i % 2 == 0);
    }
}


TEST(rapidjson_pfms, int_object_test) {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Value v;
    v.SetInt(1);
    
    for (int i = 0; i < length * 2; ++i) {
        rapidjson::Value name;
        name.SetString(std::to_string(i).c_str(), doc.GetAllocator());
        rapidjson::Value node;
        node.CopyFrom(v, doc.GetAllocator());
        doc.AddMember(name, node, doc.GetAllocator());
    }
    
    for (int i = 0; i < length * 2; ++i) {
        rapidjson::Value name;
        name.SetString(std::to_string(i).c_str(), doc.GetAllocator());
        auto iter = doc.FindMember(name);
        iter->value.SetInt(i);
    }
}


TEST(rapidjson_pfms, double_object_test) {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Value v;
    v.SetDouble(1.0);
    
    for (int i = 0; i < length * 2; ++i) {
        rapidjson::Value name;
        name.SetString(std::to_string(i).c_str(), doc.GetAllocator());
        rapidjson::Value node;
        node.CopyFrom(v, doc.GetAllocator());
        doc.AddMember(name, node, doc.GetAllocator());
    }
    
    for (int i = 0; i < length * 2; ++i) {
        rapidjson::Value name;
        name.SetString(std::to_string(i).c_str(), doc.GetAllocator());
        auto iter = doc.FindMember(name);
        iter->value.SetDouble(i * 1.0);
    }
}


TEST(rapidjson_pfms, string_object_test) {
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Value v;
    v.SetString("1.0");
    
    for (int i = 0; i < length * 2; ++i) {
        rapidjson::Value name;
        name.SetString(std::to_string(i).c_str(), doc.GetAllocator());
        rapidjson::Value node;
        node.CopyFrom(v, doc.GetAllocator());
        doc.AddMember(name, node, doc.GetAllocator());
    }
    
    for (int i = 0; i < length * 2; ++i) {
        rapidjson::Value name;
        name.SetString(std::to_string(i).c_str(), doc.GetAllocator());
        auto iter = doc.FindMember(name);
        std::string s = std::to_string(i * 1.0);
        iter->value.SetString(s.c_str(), s.size(), doc.GetAllocator());
    }
}


TEST(rapidjson_pfms, bool_array_test) {
    rapidjson::Document doc;
    doc.SetArray();
    rapidjson::Value v;
    v.SetBool(false);
    
    for (int i = 0; i < length * 100; ++i) {
        rapidjson::Value node;
        node.CopyFrom(v, doc.GetAllocator());
        doc.PushBack(v, doc.GetAllocator());
    }
    
    for (int i = 0; i < length * 100; ++i) {
        doc[i].SetBool(i % 2 == 0);
    }
}

TEST(rapidjson_pfms, int_array_test) {
    rapidjson::Document doc;
    doc.SetArray();
    rapidjson::Value v;
    v.SetInt(555);
    
    for (int i = 0; i < length * 100; ++i) {
        rapidjson::Value node;
        node.CopyFrom(v, doc.GetAllocator());
        doc.PushBack(v, doc.GetAllocator());
    }
    
    for (int i = 0; i < length * 100; ++i) {
        doc[i].SetInt(i);
    }
}


TEST(rapidjson_pfms, double_array_test) {
    rapidjson::Document doc;
    doc.SetArray();
    rapidjson::Value v;
    v.SetDouble(555.0);
    
    for (int i = 0; i < length * 100; ++i) {
        rapidjson::Value node;
        node.CopyFrom(v, doc.GetAllocator());
        doc.PushBack(v, doc.GetAllocator());
    }
    
    for (int i = 0; i < length * 100; ++i) {
        doc[i].SetDouble(i * 1.0);
    }
}


TEST(rapidjson_pfms, string_array_test) {
    rapidjson::Document doc;
    doc.SetArray();
    rapidjson::Value v;
    v.SetString("555.0");
    
    for (int i = 0; i < length * 100; ++i) {
        rapidjson::Value node;
        node.CopyFrom(v, doc.GetAllocator());
        doc.PushBack(v, doc.GetAllocator());
    }
    
    for (size_t index = 0; index < 1; ++index) {
        for (int i = 0; i < length * 100; ++i) {
            std::string s = std::to_string(i * 1.0);
            doc[i].SetString(s.c_str(), s.size());
        }
    }
    
    
}
