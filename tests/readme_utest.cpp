#include "./utest.hpp"

#include "./../json.hpp"
#include <vector>
#include <map>
#include <set>

TEST(readme, constructor) {

}

TEST(readme, Basic_Usage) {
    amo::json json_empty;                               // json_value_empty
    amo::json json_string = "ttt";                      // json_value_string
    amo::json json_number = 12.33;                      // json_value_float
    json_number = 3;                                    // json_value_signed
    json_number = 3u;                                   // json_value_unsigned
    amo::json json_boolean = true;                      // json_value_boolean
    amo::json json_null = nullptr;                      // json_value_null;
    amo::json json_object_{ amo::json_value_object };   // json_value_object;
    amo::json json_array_{ amo::json_value_array };     // json_value_array;
    
    amo::json json;                                     // empty json
    json["string"] = "amo::json";                       // {"string": "amo::json"}
    json["string"] = "amo.json";                        // {"string": "amo.json"}
    json["array"] = { 1, 0, 0, 0 };                     // {"string": "amo.json", "array": [1,0,0,0]};
    json["sub"] = { {"a", 1}, {"b", 1.1} };             // {"string": "amo.json", "array": [1,0,0,0], "sub":{"a": 1, "b": 1.1} };
    std::string str = json.to_string();                 // to string
    std::cout << str << std::endl;
    std::string s = json["string"];                     // get string from json;
    
    amo::json json2 = amo::string_reader(str);          // parse json from string
    bool has_string = json2.has("string");              // has key
    if (json2["sub"].is_object()) {                     // is json object
        amo::json sub = json2["sub"];                   // ref from json["sub"];
        amo::json sub2 = json2["sub"].get<amo::json>(); // copy from json["sub"];
        sub["a"] = 10.23;
        sub["c"] = true;
        
        std::cout << "[sub][a]=" << json2["sub"]["a"].get<int>() << std::endl;        // get<T>()
        std::cout << "[sub][a]=" << json2["sub"]["a"].get<double>() << std::endl;     // get<T>()
        std::cout << "[sub][b]=" << json2["sub"]["b"] << std::endl;                   // operator T()
        std::cout << "[sub][c]=" << json2["sub"]["c"] << std::endl;                   // operator T()
        if (sub2.has("c")) {
            // never execute
            std::cout << "[sub][c]=" << json2["sub"]["c"] << std::endl;               // operator <<
        }
    }
    
    if (json2["array"].is(amo::json_value_array)) {   // is json array
        amo::json array = json2["array"];             // ref from json2["array"]
        array[-1] = 3;                                // push back
        array.push_back(1);                           // push back
        array[0] = 2;                                 // modify value at index 0
    }
    
    std::cout << json2.to_string(4) << std::endl;     // prettify
    json2.to_file("./xxx.json");                      // write to file
    
    amo::json json3 = amo::file_reader("./xxx.json");           // parse json from file
    amo::json arr;                                              // empty json
    // arr.set_array();    // set to array
    arr.push_back(0);
    arr.push_back({1, 2, 3, 4, 5, false, true, "string txt" }); // push back with initializer_list
    std::vector<int> vec{9, 10, 11, 12 };
    arr.push_back(vec.begin(), vec.end());                      // push back with iterator
    
    // transfer json array
    for (const amo::json& p : arr) {
        std::cout << p << std::endl;
    }
    // transfer json array with array index
    arr.transfer<int>([](const int& index, amo::json & p) {
        std::cout << index << ": " << p << std::endl;
    });
    
    // transfer json object
    for (auto& p : json2) {
        std::cout << p << std::endl;   //  without key , only value
    }
    // transfer json object with key
    json2.transfer<amo::json::key_type>([](const amo::json::key_type & key, amo::json & p) {
        std::cout << key << ": " << p << std::endl;
    });
}

class custom_json_value {
public:
    const static int __json_type_value__ = 136;         // require  custom json_value_type must > 128
public:
    custom_json_value() {}
    custom_json_value(const std::string& str) : m_str(str) {}
    std::string to_string() const { return m_str; } // require
    static custom_json_value from_string(const std::string& str) { return custom_json_value(str); } // require
    std::string m_str;
};

TEST(readme, custom_json_value) {
    amo::json json = custom_json_value("123");          // construct json with custom json value
    bool b = json.is(custom_json_value::__json_type_value__);     //
    std::cout << "json value type: " << b << std::endl;
    custom_json_value value = json;                     // get custom_json_value from json
    std::cout << value.m_str << std::endl;
    custom_json_value* value2 = json;                   // get custom_json_value* from json
    std::cout << value2->m_str << std::endl;
    delete value2;                                      // delete pointer
    json = "456";
    std::shared_ptr<custom_json_value> value3 = json;   // smart ptr
    std::cout << value3->m_str << std::endl;
    
    // use custom_json_value as a normal json value type
    json.set_object();
    json["custom_json_value"] = value;
    json["custom_json_value3"] = value3;
    std::cout << json.to_string() << std::endl;
}

#include <iostream>

// simplest class
class custom_json_object {
public:
    custom_json_object() {}
    custom_json_object(const std::string& str) : m_str(str) {}
    amo::json to_json() const {
        amo::json json;
        json["m_str"] = m_str;
        return (json);
    }
    
    static custom_json_object* from_json(const amo::json& json, custom_json_object* ptr) {
        if (ptr == nullptr) {
            ptr = new custom_json_object();
        }
        
        ptr->m_str = json["m_str"].get<std::string>();
        return ptr;
    }
    std::string m_str;
    
};

// use macro
class custom_json_object2 {
public:
    typedef amo::json JsonType;     // require
public:
    custom_json_object2() { m_int = 3; }
    
    AMO_ENTITY_ARGS_GET_BEGIN_WITH_JSON_CONSTRUCTOR(custom_json_object2)
    AMO_ENTITY_ARGS_GET(m_int)  // get value from json["m_int"]
    AMO_ENTITY_ARGS_GET(m_int2)
    AMO_ENTITY_ARGS_GET(m_vec)
    AMO_ENTITY_ARGS_GET(m_custom_json_object)
    
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(custom_json_object2)
    AMO_ENTITY_ARGS_SET(m_int) // set value to json["m_int"]
    AMO_ENTITY_ARGS_SET(m_int2)
    AMO_ENTITY_ARGS_SET(m_vec)
    AMO_ENTITY_ARGS_SET(m_custom_json_object)
    AMO_ENTITY_ARGS_SET_END()
    
    int m_int;
    std::shared_ptr<int> m_int2;
    std::vector<int> m_vec;
    std::shared_ptr<custom_json_object>  m_custom_json_object;
};

TEST(readme, custom_json_object) {
    custom_json_object json_class;
    json_class.m_str = "3";
    amo::json simplejson = json_class;
    std::cout << simplejson << std::endl;       // {"m_str":"3"}
    
    custom_json_object2 c1;
    c1.m_vec.push_back(1);
    c1.m_vec.push_back(2);
    
    amo::json json = c1;
    std::cout << c1.to_string() << std::endl;   // {"m_int":3,"m_vec":[1,2]}
    std::cout << json.to_string() << std::endl; // {"m_int":3,"m_vec":[1,2]}
    json["m_int2"] = 3;
    
    custom_json_object2 c2 = json;
    std::cout << *c2.m_int2 << std::endl; // 3
    
    json["m_custom_json_object"] = custom_json_object("657");
    std::shared_ptr<custom_json_object2> c3 = json;
    std::cout << c3->m_custom_json_object->m_str << std::endl; // 567
    std::cout << c3->to_string() << std::endl;//{"m_int":3,"m_int2":3,"m_vec":[1,2],"m_custom_json_object":{"m_str":"657"}}
}


