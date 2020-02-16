#include <iostream>

#include "./../json.hpp"
#include "./utest.hpp"

#include <fstream>
#include <array>
#include <unordered_map>
#include <thread>
#include <map>
#include <utility>
#include "make_json.hpp"

//#include "nlohmann/json.hpp"

namespace amo {
    namespace JSON_IMPL {
        /* template<> inline std::string to_string(const amo::date_time& val) {
        return val.to_string();
        }
        
        template<> inline amo::date_time lexical_cast(const std::string& val) {
        return amo::date_time::from_string(val);
        }
        
        template<> inline std::string to_string(const amo::uuid& val) {
        return val.to_string();
        }
        
        template<> inline amo::uuid lexical_cast(const std::string& val) {
        return amo::uuid::from_string(val);
        }*/
    }
    
    // 自定义类型
    /*template<> struct json_value_proxy<json_type::ObjectType::MapType, std::string > {
    	typedef json_type::ObjectType::MapType type;
    	typedef json_type::ObjectType::DataType Data;
    	static const int32_t value = 2;
    	json_value_proxy(const Data& d_) : d(*(Data*)& d_) {
    	}
    	type get_value()  const {
    		return *((json_type::ObjectType::MapType*)(d.o.elements));
    	}
    	void set_value(const type& val, const std::shared_ptr<memory_allocator<> >& allocator) {
    		d.ss.flag = json_value_object;
    		void* ptr = allocator->allocate(sizeof(MapType));
    		d.o.elements = new(ptr) json_type::ObjectType::MapType(allocator);
    
    		for (auto& p : val) {
    			((json_type::ObjectType::MapType*)(d.o.elements))->insert({ p.first, p.second.clone() });
    		}
    	}
    	void to_string(std::ostream& stream) const {
    		json::ObjectType object;
    		object.d = d;
    		return object.to_string(stream);
    	};
    	Data& d;
    };*/
    
    // 自定义类型
    template<typename  ObjectType> struct json_value_proxy <ObjectType, std::vector<ObjectType> > {
        static const int32_t value = json_value_array;
        static const int32_t compatible = json_value_string;  // 兼容类型为string
        typedef typename ObjectType::DataType DataType;
        typedef typename ObjectType::JsonAllocType JsonAllocType;
        typedef typename ObjectType::ArrayType ArrayType;
        DataType& d;
        
        json_value_proxy(const DataType& d_) : d(*(DataType*) & d_) {}
        
        std::vector<ObjectType> get_value() const {
            return *d.a.elements;
        }
        
        void set_value(const std::vector<ObjectType>& val, const JsonAllocType& allocator) {
            d.ss.flag = value;
            void* ptr = allocator->allocate(sizeof(ArrayType));
            d.a.elements = new (ptr)ArrayType(allocator);
            
            for (auto& p : val) {
                auto& object = typename ObjectType::TypeTraits().push_back_object(d.a.elements);
                object.copy(p, allocator);
            }
        }
        
        template<typename P> void to_string(P& stream) const {
            ObjectType object;
            object.d = d;
            return object.to_string(stream);
        }
        
        
        
    };
}

TEST(json, type) {


    std::string str = "{ \"aaa\":3, \"bbb\":\"3.0\", \"ccc\":true,\"ddd\":null } ";
    //json_type json12 = str;
    //json_type json13 = "1232";
    //json_type json14 = { "123", 3 };
    json_type json(amo::string_reader{str.c_str()});
    json_type json1 = std::stringstream(str);
    std::string ssss = json.to_string();
    std::string ssss1 = json1.to_string();
    json["eee"] = 3;
    json["fff"] = "3.0";
    json["ggg"] = true;
    json["hhh"] = nullptr;
    
    EXPECT_EQ(json["aaa"].get_type(), amo::value_t::json_value_unsigned);
    EXPECT_EQ(json["bbb"].get_type(), amo::value_t::json_value_string);
    EXPECT_EQ(json["ccc"].get_type(), amo::value_t::json_value_boolean);
    EXPECT_EQ(json["ddd"].get_type(), amo::value_t::json_value_null);
    
    EXPECT_EQ(json["eee"].get_type(), amo::value_t::json_value_integer);
    EXPECT_EQ(json["fff"].get_type(), amo::value_t::json_value_string);
    EXPECT_EQ(json["ggg"].get_type(), amo::value_t::json_value_boolean);
    EXPECT_EQ(json["hhh"].get_type(), amo::value_t::json_value_null);
    
    
    int32_t a = json["aaa"];
    std::string b = json["bbb"];
    bool c = json["ccc"];
    std::nullptr_t d = (std::nullptr_t)json["ddd"].get<std::nullptr_t>();
    
    int32_t e = json["eee"];
    std::string f = json["fff"];
    bool g = json["ggg"];
    std::nullptr_t h = json["hhh"].get<std::nullptr_t>();
    int32_t md = (int32_t)json["aaa"];
    EXPECT_TRUE((int32_t)json["aaa"] == 3);
    EXPECT_EQ(b, "3.0");
    EXPECT_EQ(c, true);
    EXPECT_EQ(json["hhh"].to_string(), "null");
    EXPECT_EQ(e, 3);
    EXPECT_EQ(f, "3.0");
    EXPECT_EQ(g, true);
    EXPECT_TRUE(h == nullptr);
}

TEST(json, set_object) {
    json_type json;
    json.set_object();
    EXPECT_EQ(json.is_object(), true);
    json = 3;
    EXPECT_EQ(json.is_object(), false);
    json.set_object();
    EXPECT_EQ(json.is_object(), true);
}

TEST(json, set_array) {
    json_type json;
    json.set_array();
    EXPECT_EQ(json.is_array(), true);
    json = 3;
    EXPECT_EQ(json.is_array(), false);
    json.set_array();
    EXPECT_EQ(json.is_array(), true);
}


// 强制类型转换
TEST(json, operatorT) {
    json_type json = 3;
    int val = json;
    EXPECT_EQ(val, 3);
    
    json = 1.32;
    bool c = (bool)3;
    bool b = (bool)json;
    
    if (b == true) {
        std::cout << 3 << std::endl;
    }
    
    if (json.get<bool>()) {
        std::cout << 4 << std::endl;
    }
    
    EXPECT_TRUE(json.get<bool>());
    EXPECT_EQ(json, 1.32);
    std::string str = json.to_string();
    EXPECT_NE(str, "true");
}

TEST(json, get) {
    json_type json;
    EXPECT_EQ(json.get<int>(), 0);
    EXPECT_EQ(json.get<bool>(), false);
    EXPECT_EQ(json.get<double>(), 0.0);
    EXPECT_EQ(json.get<std::nullptr_t>() == nullptr, true);
    EXPECT_EQ(json.get<std::string>(), "");
    json = 3;
    EXPECT_EQ(json.get<int>(), 3);
    json = 3e10;
    EXPECT_EQ(json.get<int64_t>(), 3e10);
    EXPECT_EQ(json.get<double>(), 3e10);
    json = 3.10;
    EXPECT_EQ(json.get<double>(), 3.10);
    json = "123";
    EXPECT_EQ(json.get<std::string>(), "123");
    json = nullptr;
    EXPECT_EQ(json.get<std::nullptr_t>() == nullptr, true);
    json = { 1, 2, 3, 4 };
    EXPECT_EQ(json.get<json_type>()[0].get<int>(), 1);
    EXPECT_EQ(json.get<json_type>()[1].get<int>(), 2);
    EXPECT_EQ(json.get<json_type>()[2].get<int>(), 3);
    EXPECT_EQ(json.get<json_type>()[3].get<int>(), 4);
    json = { {"a", 1}, {"b", 2} };
    EXPECT_EQ(json.get<json_type>()["a"].get<int>(), 1);
    json_type a = json["a"]; // 引用
    a = 3;
    EXPECT_EQ(json.get<json_type>()["a"].get<int>(), 3);
    json_type b = json["b"].get<json_type>(); // 拷贝
    b = 4;
    EXPECT_NE(json.get<json_type>()["b"].get<int>(), 4);
    EXPECT_EQ(json["b"].get<int>(), 2);
    json = amo::custom_class("123");
    EXPECT_EQ(json.get<amo::custom_class>().to_string(), amo::custom_class("123").to_string());
}

TEST(json, find) {
    json_type arr(amo::json_value_array);
    arr.push_back({ 1, 2, 3 });
    EXPECT_EQ(arr.find(0).get_value<int>(arr.get_allocator()), 1);
    // 直接插件JSON数据
    arr.find(0).set_value<int>(2, arr.get_allocator());
    EXPECT_EQ(arr.find(0).get_value<int>(arr.get_allocator()), 2);
    
    json_type json(amo::json_value_object);
    json["a"] = 1;
    json["b"] = 2;
    json["c"];
    json.find("d").set_value(4, json.get_allocator());
    json.find("d").set_value(4.23432, json.get_allocator());
    json.find("c").set_value("12312", json.get_allocator());
    EXPECT_EQ(json["d"], 4.23432);
    EXPECT_EQ(json["c"].get<std::string>(), "12312");
}

TEST(json, operator_get) {
    json_type json;
    json["a"] = true;  // 默认会将空json转换为JsonObject或JsonArray
    json["b"] = 12;
    json["c"] = json;
    json["c"]["a"] = false;
    
    // 注意这里，拿引用
    json_type c = json["c"];
    c["b"] = 2;
    EXPECT_EQ(json["c"]["b"].get<int>(), c["b"].get<int>());
    c["b"] = c;
    EXPECT_EQ(json["c"]["b"]["b"].get<int>(), c["b"]["b"].get<int>());
    
    // 这里是拿拷贝
    json_type c1 = json["c"].get<json_type>();
    c1["b"] = 3;
    EXPECT_NE(json["c"]["b"].get<int>(), c1["b"].get<int>());
    
    std::cout << json.to_string() << std::endl;
    
    try {
        json[1] = 3;
        EXPECT_TRUE(false);
    } catch (const std::exception&) {
        EXPECT_TRUE(true);
    }
    
    try {
        json = 2;
        json[1] = 3;
        EXPECT_TRUE(false);
    } catch (const std::exception&) {
        EXPECT_TRUE(true);
    }
    
    json_type arr = { 1, {1, 2, 3, {1, 2, 3}},
        {"a", {1, 2, 3}},
        4, 5, "str", true, false, amo::custom_class("11")
    };
    EXPECT_EQ(arr[1][3][2], 3);
    EXPECT_EQ(arr[2]["a"][2], 3);
}

TEST(json, put) {
    json_type json;
    json.put("aaa", 1);
    json.put("bbb", 2);
    json.put("ccc", json);              // 没问题
    json.put("ddd", amo::custom_class("1"));
    //json.put("ddd", std::move(json)); // 错误的用法 不要自己move自己
    //json.put("eee", json["aaa"]);//错误用法
    json.put("eee", json["aaa"].get<json_type>()); //ok
    std::cout << json.to_string(4) << std::endl;
}

TEST(json, push_back) {
    auto a1 = std::is_array<int>::value;
    auto a2 = std::is_array<std::vector<int>>::value;
    json_type arr;
    arr.push_back(1).push_back(2).push_back(nullptr).push_back(true);
    arr.push_back({ 1, 2, 3, 4, 5, 6, true, false, "ddddd"});
    arr.push_back(json_type({"aa", 1}));
    EXPECT_EQ(arr.to_string(), R"([1,2,null,true,1,2,3,4,5,6,true,false,"ddddd",{"aa":1}])");
    
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
    arr.push_back(v.begin(), v.end());
    
    std::set<int> v2 = { 1, 2, 3, 4, 5, 6 };
    arr.push_back(v2.begin(), v2.end());
    
    int v3[6] = { 1, 2, 3, 4, 5, 6 };
    arr.push_back(&v3[0], &v3[0] + 6);
    arr.push_back(std::begin(v3), std::end(v3));
    std::cout << arr.to_string() << std::endl;
}

TEST(json, erase) {
    json_type arr = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr[0], 1);
    arr.erase(0);    // 移除索引为0的数据
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0], 2);
    arr.erase(1, 2); // 从索引2开始，移除两个数据
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[1], 5);
    
    json_type json;
    json["a"] = 1;
    json["b"] = 2;
    json["c"] = 3;
    json["d"] = 4;
    EXPECT_EQ(json["a"], 1);
    json.erase("a");
    EXPECT_EQ(json.size(), 3);
    EXPECT_EQ(json["a"].is_empty(), true);
    EXPECT_EQ(json.size(), 4);
}
TEST(json, transfer) {
    json_type json;
    
    try {
        // JSON未初始，默认为空类型，空类型不允许遍历
        for (auto& p : json) {}
        
        EXPECT_TRUE(false);
    } catch (const std::exception&) {
        EXPECT_TRUE(true);
    }
    
    json.set_array();
    json.push_back(1);
    json.push_back({ 1, 1, 1, 1 });
    EXPECT_EQ(json.size(), 5);
    
    //
    for (auto& p : json) {
        EXPECT_EQ(p.to_string(), "1");
    }
    
    //
    for (auto iter = json.begin(); iter != json.end(); ++iter) {
        // 当Json为Array时，下面的方法不支持
        try {
            std::cout << iter->first << std::endl;
            EXPECT_TRUE(false);// 这里永远都不能到达
        } catch (const std::exception&) {
            EXPECT_TRUE(true);
        }
    }
    
    json.push_back({ "a", 1 });
    json.push_back({ {"b", 2} });
    EXPECT_EQ(json.size(), 8);
    std::cout << json.to_string() << std::endl;
    json.set_object();
    json["a"] = 1;
    json["b"] = 1;
    EXPECT_EQ(json.size(), 2);
    
    for (auto& p : json) {
        EXPECT_EQ(p.to_string(), "1");
    }
    
    for (auto iter = json.begin(); iter != json.end(); ++iter) {
        iter.value();   // 与json_data_object关联的json
        iter.key();     //  key
        iter->first;     // key&, 只能是jsonObject的情况下调用
        iter->second;    // json_data_object& 只能是jsonObject的情况下调用
        
        EXPECT_TRUE(json[iter->first] == json_type(iter->second, json.get_allocator()));
        //std::cout << iter->first << iter->second << std::endl;
    }
    
    std::cout << json.to_string() << std::endl;
    std::function<void(const std::string&, json_type&)> fn = [ = ](const std::string & key, json_type & p) {
        //std::cout << key << std::endl;
        return;
    };
    
    json.transfer(fn);
    // 一种较好的json遍历的方式
    json.transfer<json_type::key_type>([ = ](
    const json_type::key_type & key, json_type & p)->void {
        std::cout << key << std::endl;
        return;
    });
    
    json.set_array();
    json.push_back({ 1, 2, 3, 4, 5, 6, 7, 8, false });
    
    EXPECT_EQ(json.size(), 9);
    json.transfer<int>([](const int& index, json_type & p) {
        std::cout << index << "," << p.to_string() << std::endl;
    });
    
    // 直接从data_object上去遍历,需要自行保存数据安全
    for (auto& p : * (json.get_data_object().d.a.elements)) {
        std::cout << p.to_string() << std::endl;
    }
    
    json.set_object();
    json["a"] = 1;
    json["b"] = false;
    json["c"] = 1.2;
    EXPECT_EQ(json.size(), 3);
    
    for (auto& p : * (json.get_data_object().d.o.elements)) {
        json_type(p.second, json.get_allocator()) = 23;
        std::cout << p.first << ", " << p.second.to_string() << std::endl;
    }
}
TEST(json, keys) {
    json_type json;
    json["a"] = 1;
    json["b"] = "af";
    EXPECT_EQ(json.keys().size(), 2);
}

TEST(json, has) {
    json_type json;
    json["a"] = 1;
    json["b"] = "af";
    
    EXPECT_EQ(json.has("a"), true);
    EXPECT_EQ(json.has("b"), true);
    EXPECT_EQ(json.has("c"), false);
}


TEST(json, contains_key) {
    json_type json1;
    json1.put("aa", 1);
    json1.put("bb", "2");
    json_type json2;
    json2.put("aa", 3);
    json1["cc"] = json2;
    EXPECT_EQ(json1["cc"].contains_key("aa"), true);
    EXPECT_EQ(json1.contains_key("cc"), true);
    EXPECT_EQ(json1.contains_key("dd"), false);
}



TEST(json, is) {

    std::string str = make_json().to_string();// "{\"aaa\":3, \"bbb\":\"3.0\", \"ccc\":true, \"ddd\":null }";
    json_type json(amo::string_reader{ str });
    json["eee"] = 3;
    json["fff"] = "3.0";
    json["ggg"] = true;
    json["hhh"] = nullptr;
    EXPECT_EQ(json["aaa"].is<amo::empty_t>(), true);
    EXPECT_EQ(json["bbb"].is<amo::empty_t>(), true);
    EXPECT_EQ(json["ccc"].is<amo::empty_t>(), true);
    EXPECT_EQ(json["ddd"].is<amo::empty_t>(), true);
    
    EXPECT_EQ(json["eee"].is<int32_t>(), true);
    EXPECT_EQ(json["fff"].is<std::string>(), true);
    EXPECT_EQ(json["ggg"].is<bool>(), true);
    EXPECT_EQ(json["hhh"].is<std::nullptr_t>(), true);
    
    EXPECT_EQ(json["vec1"].is<json_type>(), true);
    EXPECT_EQ(json["vec3"].is<json_type>(), true);
    
    EXPECT_EQ(json["vec1"][0].is<std::string>(), true);
    EXPECT_EQ(json["vec2"][0].is<int32_t, uint32_t>(), true);
    
    json_type m_jsoninfo1 = json["m_jsoninfo2"]["m_jsoninfo1"];
    
    EXPECT_EQ(m_jsoninfo1["m_bool"].is(amo::value_t::json_value_boolean), true);
    EXPECT_EQ(m_jsoninfo1["m_int8_t"].is(amo::value_t::json_value_unsigned), true);
    EXPECT_EQ(m_jsoninfo1["m_int16_t"].is(amo::value_t::json_value_unsigned), true);
    EXPECT_EQ(m_jsoninfo1["m_int32_t"].is(amo::value_t::json_value_unsigned), true);
    EXPECT_EQ(m_jsoninfo1["m_int64_t"].is(amo::value_t::json_value_unsigned), true);
    EXPECT_EQ(m_jsoninfo1["m_uint8_t"].is(amo::value_t::json_value_unsigned), true);
    EXPECT_EQ(m_jsoninfo1["m_uint16_t"].is(amo::value_t::json_value_unsigned), true);
    EXPECT_EQ(m_jsoninfo1["m_uint32_t"].is(amo::value_t::json_value_unsigned), true);
    EXPECT_EQ(m_jsoninfo1["m_uin64_t"].is(amo::value_t::json_value_unsigned), true);
    EXPECT_EQ(m_jsoninfo1["m_float"].is(amo::value_t::json_value_float), true);
    EXPECT_EQ(m_jsoninfo1["m_double"].is(amo::value_t::json_value_float), true);
    EXPECT_EQ(m_jsoninfo1["m_string"].is(amo::value_t::json_value_string), true);
    
}

TEST(json, to_array) {

    json_type json = amo::string_reader{ "[1,2,3,4,5,6, false, true, 1.33]" };
    std::vector<json_type> vec = json.to_array();
    
    for (size_t i = 0; i < vec.size() ; ++i) {
        EXPECT_EQ(vec[i] == json[i], true);
    }
    
    json_type arr;
    //arr["ad"] = 3;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back("aa");
    arr.to_array();
    EXPECT_EQ(arr.size(), 3);
}

struct POD1 {
    int a;
    char b[12];
    long d;
};

struct POD2 {
    POD2() {}
    int a;
    char b[12];
    long d;
};

struct POD3 {
    const static int aaa = 3;
    int a;
    char b[12];
    long d;
};
struct POD4 {
    const static int __json_value_type__ = 3;
    int a;
    char b[12];
    long d;
    std::string to_string() const { return "3"; }
    static POD4 from_string(const std::string& from) { return POD4(); }
};
TEST(json, to_string) {
    std::cout << std::is_trivial<POD1>::value << std::endl;
    std::cout << std::is_trivial<POD2>::value << std::endl;
    std::cout << std::is_trivial<POD3>::value << std::endl;
    std::cout << std::is_trivial<POD4>::value << std::endl;
    std::cout << std::is_pod<POD2>::value << std::endl;
    EXPECT_EQ(json_type(true).to_string(), "true");
    EXPECT_EQ(json_type(false).to_string(), "false");
    json_type json1(amo::json_value_array);
    json1.push_back(1);
    json1.push_back("1");
    json1.push_back(json_type());
    std::string ss = json1.to_string();
    std::string s2 = R"([1,"1"])";
    EXPECT_EQ(json1.to_string(), R"([1,"1"])");
    EXPECT_EQ(json_type().to_string(), "");
    EXPECT_EQ(json_type(3).to_string(), "3");
    EXPECT_EQ(json_type("3").to_string(), "\"3\"");
}

class test1 {
public:
    test1(const json_type& json) {
    
    }
};


TEST(json, test12) {
    json_type arr(amo::json_value_array);
    arr.push_back(1);
    arr.push_back(1);
    
    //std::vector<int> vec = arr;
    test1 t1 = arr;
}


TEST(json, misc) {

    json_type jso2;
    jso2 = 1.0;
    json_type jt2;
    jt2 = 3;
    std::string sssss = jso2.to_string();
    std::string str = make_json().to_string();// "{\"aaa\":3, \"bbb\":\"3.0\", \"ccc\":true, \"ddd\":null }";
    json_type json(amo::string_reader{str});
    json["eee"] = 3;
    json["fff"] = "3.0";
    json["ggg"] = true;
    json["hhh"] = nullptr;
    EXPECT_EQ(json["aaa"].get_type(), amo::value_t::json_value_empty);
    EXPECT_EQ(json["bbb"].get_type(), amo::value_t::json_value_empty);
    EXPECT_EQ(json["ccc"].get_type(), amo::value_t::json_value_empty);
    EXPECT_EQ(json["ddd"].get_type(), amo::value_t::json_value_empty);
    
    EXPECT_EQ(json["eee"].get_type(), amo::value_t::json_value_integer);
    EXPECT_EQ(json["fff"].get_type(), amo::value_t::json_value_string);
    EXPECT_EQ(json["ggg"].get_type(), amo::value_t::json_value_boolean);
    EXPECT_EQ(json["hhh"].get_type(), amo::value_t::json_value_null);
    
    
    EXPECT_EQ(json["vec1"].get_type(), amo::value_t::json_value_array);
    EXPECT_EQ(json["vec3"].get_type(), amo::value_t::json_value_array);
    EXPECT_EQ(json["vec1"][0].get_type(), amo::value_t::json_value_string);
    EXPECT_EQ(json["vec2"][0].get_type(), amo::value_t::json_value_unsigned);
    
    json_type m_jsoninfo1 = json["m_jsoninfo2"]["m_jsoninfo1"];
    
    EXPECT_EQ(m_jsoninfo1["m_bool"].get_type(), amo::value_t::json_value_boolean);
    //info.put("m_char", 'c');
    EXPECT_EQ(m_jsoninfo1["m_int8_t"].get_type(), amo::value_t::json_value_unsigned);
    EXPECT_EQ(m_jsoninfo1["m_int16_t"].get_type(), amo::value_t::json_value_unsigned);
    EXPECT_EQ(m_jsoninfo1["m_int32_t"].get_type(), amo::value_t::json_value_unsigned);
    EXPECT_EQ(m_jsoninfo1["m_int64_t"].get_type(), amo::value_t::json_value_unsigned);
    EXPECT_EQ(m_jsoninfo1["m_uint8_t"].get_type(), amo::value_t::json_value_unsigned);
    EXPECT_EQ(m_jsoninfo1["m_uint16_t"].get_type(), amo::value_t::json_value_unsigned);
    EXPECT_EQ(m_jsoninfo1["m_uint32_t"].get_type(), amo::value_t::json_value_unsigned);
    EXPECT_EQ(m_jsoninfo1["m_uin64_t"].get_type(), amo::value_t::json_value_unsigned);
    EXPECT_EQ(m_jsoninfo1["m_float"].get_type(), amo::value_t::json_value_float);
    EXPECT_EQ(m_jsoninfo1["m_double"].get_type(), amo::value_t::json_value_float);
    EXPECT_EQ(m_jsoninfo1["m_string"].get_type(), amo::value_t::json_value_string);
    
    int32_t a = json["aaa"];
    std::string b = json["bbb"];
    bool c = json["ccc"];
    std::nullptr_t d = (std::nullptr_t)json["ddd"].get<std::nullptr_t>();
    
    int32_t e = json["eee"];
    std::string f = json["fff"];
    bool g = json["ggg"];
    std::nullptr_t h = json["hhh"].get<std::nullptr_t>();
    std::nullptr_t  t = std::nullptr_t();
    std::nullptr_t t2 = t;
    
    if (t == nullptr) {
        std::cout << "null" << std::endl;
    }
}


TEST(json, construct) {

    //json_type custom1 = amo::custom_class("2341");
    //amo::custom_class c1 = custom1;
    
    std::stringstream stream;
    stream << "3";
    std::cout << sizeof(json_type) << std::endl;
    json_type json1;
    json_type json2(amo::json_value_array);
    json_type json3({ "\"3\"", 3 });
    json_type json3_2({ "\"3\"", 3, {} });
    json_type json3_1("\"3\"");
    //json_type json3_2({ stream });
    json_type json3_3("\"3\"");
    json_type json66 = { "234" };
    json_type json77 = "12312";
    json_type json4(amo::string_reader("{\"aa\":1}"));
    //json_type json5({ {"aa", 1}, {"bb", "2"} });
    json_type json6 = (json4);
    json_type json7(stream);
    std::string sb11 = json7.to_string();
    std::cout << sb11 << std::endl;
    json_type json18 = "{ \"aaa\":3, \"bbb\":\"3.0\", \"ccc\":true,\"ddd\":null } "_json_;
    
    std::ifstream ifs("test.json", std::ios::in | std::ios::binary);
    
    json_type json8(ifs);
    json_type json9 = json8;
    EXPECT_EQ(json1.get_type(), amo::json_value_empty);
    EXPECT_EQ(json2.get_type(), amo::json_value_array);
    EXPECT_EQ(json3.get_type(), amo::json_value_object);
    EXPECT_EQ(json3_2.get_type(), amo::json_value_array);
    EXPECT_EQ(json4.get_type(), amo::json_value_object);
    //EXPECT_EQ(json5.is_object(), true);
    EXPECT_EQ(json6.get_type(), amo::json_value_object);
    EXPECT_EQ(json7.get_type(), amo::json_value_unsigned);
    EXPECT_EQ(json8.is_empty(), true);
    EXPECT_EQ(json9.is_empty(), true);
    
}


TEST(json, join) {
    json_type json1;
    json1.put("aa", 1);
    json1.put("bb", "2");
    std::string cc = "cc";
    json1.put(cc, 3);
    json_type json2;
    json2.put("aa", 3);
    
    json1.join(json2);
    EXPECT_EQ(json1["aa"].get<int32_t>(), 3);
    
    json2["dd"] = 75;
    json_type json3 = json1;
    json3["ccc"] = json1;
    json3["ccc"].join(json2);
    EXPECT_EQ(json3["ccc"]["dd"].get<int32_t>(), 75);
}

TEST(json, put_child) {

    json_type json1;
    json1.put("aa", 1);
    json1.put("bb", "2");
    json_type json2;
    json2.put("aa", 3);
    json1["cc"] = json2;
    EXPECT_EQ(json1["cc"]["aa"].get<int32_t>(), 3);
    
}

TEST(json, put_rreference) {

    json_type json1;
    json1.put("aa", 1);
    json1.put("bb", "2");
    json_type json2;
    json2.put("aa", 3);
    json1["cc"] = json2;
    json1["dd"] = make_json();
    EXPECT_EQ(json1["cc"]["aa"].get<int32_t>(), 3);
    
}


class aaaa {
public:
    std::string to_string() const {
        return "123123";
    }
};

namespace amo {

    template<> inline aaaa from_string(const std::string& val) {
        return aaaa();
    }
    template<> inline std::string to_string<aaaa>(const aaaa& val) {
        return "123123";
    }
    
}


TEST(json, array_option) {
    json_type vec(amo::json_value_array);
    vec.push_back(1);
    vec.push_back("1");
    vec.push_back(json_type(amo::json_value_object));
    
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0].get<int32_t>(), 1);
    EXPECT_EQ(vec[1].get<std::string>(), "1");
    EXPECT_EQ(vec[2].get_type(), amo::json_value_object);
}


TEST(json, format) {
    json_type json1(amo::json_value_array);
    //json1.set_array();
    json1.push_back(1);
    json1.push_back("1");
    json_type json2;
    json2.put("aa", 3);
    json2.put("bb", true);
    json2.put("cc", "dddd");
    json1.push_back(json2);
    json1.push_back(json2);
    json1.push_back(json2);
    
    std::fstream ifs("./format.json", std::ios::in);
    json_type json3(ifs);
}


TEST(json, iterator2) {
    json_type json1(amo::json_value_array);
    //json1.set_array();
    json1.push_back(1);
    json1.push_back("1");
    json_type json2;
    json2.put("aa", 3);
    json2.put("bb", true);
    json2.put("cc", "dddd");
    json1.push_back(json2);
    json1.push_back(json2);
    json1.push_back(json2);
    
    auto iter = json1.begin();
    
    for (const auto& p : json1) {
        std::cout << p.to_string() << std::endl;
    }
    
    for (auto& p : json2) {
        //std::cout << p.key() << ":" << p.value() << std::endl;
        
    }
    
    
}


