#include "./../json.hpp"
typedef amo::json json_type;

namespace {

    //dde.set_value(33);
    
    int32_t length = 10000;
    json_type make_json2() {
        json_type info;
        info.put("m_bool", true);
        //info.put("m_char", 'c');
        info.put("m_int8_t", 8);
        info.put("m_int16_t", 16);
        info.put("m_int32_t", 32);
        info.put("m_int64_t", 64);
        info.put("m_uint8_t", 8u);
        info.put("m_uint16_t", 16u);
        info.put("m_uint32_t", 32u);
        info.put("m_uin64_t", 64u);
        info.put("m_float", 1.0);
        info.put("m_double", 2.22);
        info.put("m_string", "string txt");
        info["m_string"].put("string txt");
        /*   info.put("m_strine", u8"kd wer\\r\\n中方式\\u3053\\u3093\\u306b\\u3061\\u306f\\u4e16\\u754c\\uff0112312中文");
        info.put("m_string2", "string txt11111111111111111111111111111111111111111111");*/
        
        //std::string st = info.to_string();
        return info;
    }
    json_type make_json() {
    
    
    
        json_type vec1(amo::json_value_array);
        vec1.push_back("1");
        vec1.push_back("2");
        vec1.push_back("3");
        
        
        json_type vec2(amo::json_value_array);
        vec2.push_back(4);
        vec2.push_back(5);
        vec2.push_back(6);
        
        json_type vec3(amo::json_value_array);
        
        {
            json_type arr3(amo::json_value_array);
            arr3.push_back(7);
            arr3.push_back(8);
            arr3.push_back(9);
            /*arr3.push_back(  u8"kd wer\\r\\n中方式\\u3053\\u3093\\u306b\\u3061\\u306f\\u4e16\\u754c\\uff0112312中文");
            arr3.push_back(  "string txt11111111111111111111111111111111111111111111");*/
            
            vec3.push_back(arr3);
            vec3.push_back(arr3);
            vec3.push_back(arr3);
        }
        
        
        json_type json;
        json.put("vec1", vec1);
        json.put("vec2", vec2);
        json.put("vec3", vec3);
        ;
        
        json_type info;
        info.put("m_bool", true);
        //info.put("m_char", 'c');
        info.put("m_int8_t", 8);
        info.put("m_int16_t", 16);
        info.put("m_int32_t", 32);
        info.put("m_int64_t", 64);
        info.put("m_uint8_t", 8u);
        info.put("m_uint16_t", 16u);
        info.put("m_uint32_t", 32u);
        info.put("m_uin64_t", 64u);
        info.put("m_float", 1.0);
        info.put("m_double", 2.22);
        info.put("m_string", "string txt");
        /*	info.put("m_strine2", u8"kd wer\\r\\n中方式\\u3053\\u3093\\u306b\\u3061\\u306f\\u4e16\\u754c\\uff0112312中文");
        	info.put("m_string3", "string txt11111111111111111111111111111111111111111111");*/
        
        
        // json.put("m_jsoninfo2", info);
        // json.put("m_jsoninfo3", info);
        //
        // std::cout << json.to_string() << std::endl;
        json_type jsoninfoclass;
        jsoninfoclass.put("m_jsoninfo1", info);
        jsoninfoclass.put("m_jsoninfo2", info);
        
        json.put("m_jsoninfo2", jsoninfoclass);
        json.put("m_jsoninfo3", jsoninfoclass);
        
        // std::cout << json.to_string() << std::endl;
        json_type arr(amo::json_value_array);
        arr.push_back(jsoninfoclass);
        arr.push_back(jsoninfoclass);
        arr.push_back(jsoninfoclass);
        arr.push_back(jsoninfoclass);
        
        json.put("m_jsoninfo4", arr);
        json.put("m_jsoninfo5", arr);
        
        json_type arr2(amo::json_value_array);
        arr2.push_back(arr);
        arr2.push_back(arr);
        arr2.push_back(arr);
        json.put("m_jsoninfo6", arr2);
        
        return json;
    }
    
    json_type make_json3() {
    
    
    
        json_type vec1(amo::json_value_array);
        /*vec1.push_back("1");
        vec1.push_back("2");
        vec1.push_back("3");
        */
        
        json_type vec2(amo::json_value_array);
        /*vec2.push_back(4);
        vec2.push_back(5);
        vec2.push_back(6);*/
        
        json_type vec3(amo::json_value_array);
        
        {
            json_type arr3(amo::json_value_array);
            /*arr3.push_back(7);
            arr3.push_back(8);
            arr3.push_back(9);*/
            
            vec3.push_back(arr3);
            vec3.push_back(arr3);
            vec3.push_back(arr3);
        }
        
        
        json_type json;
        /*	json.put("vec1", vec1);
        	json.put("vec2", vec2);
        	json.put("vec3", vec3);*/
        ;
        
        json_type info;
        //info.put("m_bool", true);
        ////info.put("m_char", 'c');
        //info.put("m_int8_t", 8);
        //info.put("m_int16_t", 16);
        //info.put("m_int32_t", 32);
        //info.put("m_int64_t", 64);
        //info.put("m_uint8_t", 8u);
        //info.put("m_uint16_t", 16u);
        //info.put("m_uint32_t", 32u);
        //info.put("m_uin64_t", 64u);
        //info.put("m_float", 1.0);
        //info.put("m_double", 2.22);
        //info.put("m_string", "string txt");
        
        json.put("m_jsoninfo2", info);
        json.put("m_jsoninfo3", info);
        
        
        json_type jsoninfoclass;
        jsoninfoclass.put("m_jsoninfo1", info);
        jsoninfoclass.put("m_jsoninfo2", info);
        
        json.put("m_jsoninfo2", jsoninfoclass);
        json.put("m_jsoninfo3", jsoninfoclass);
        
        json_type arr(amo::json_value_array);
        arr.push_back(jsoninfoclass);
        arr.push_back(jsoninfoclass);
        arr.push_back(jsoninfoclass);
        arr.push_back(jsoninfoclass);
        
        json.put("m_jsoninfo4", arr);
        json.put("m_jsoninfo5", arr);
        
        json_type arr2(amo::json_value_array);
        arr2.push_back(arr);
        arr2.push_back(arr);
        arr2.push_back(arr);
        json.put("m_jsoninfo6", arr2);
        
        return json;
    }
}


namespace amo {
    class custom_class {
    public:
        const static int __json_type_value__ = 11111;
    public:
        custom_class() { }
        custom_class(const std::string& str) : m_str(str) { }
        std::string to_string() const { return m_str; }
        static custom_class from_string(const std::string& str) { return custom_class(str); }
        std::string m_str;
    };
    
    static inline std::string to_string(const amo::custom_class& val) {
        return	val.to_string();
    }
    
    template<> inline amo::custom_class from_string(const std::string& str) {
        return custom_class::from_string(str);
    }
    
    class custom_class2 {
    public:
        custom_class2() { }
        custom_class2(const std::string& str) : m_str(str) { }
        json_type to_json() const { return json_type(); }
        static custom_class2* from_json(const json_type& json, custom_class2* ptr) {
            if (ptr == nullptr) {
                ptr = new custom_class2();
            }
            
            ptr->m_str = json["m_str"].get<std::string>();
            return ptr;
        }
        std::string m_str;
    };
    
    class custom_class3 {
    public:
        json_type to_json() const { return json_type(); }
    public:
        custom_class3() {}
        custom_class3(const json_type& str) : m_str(str["m_string"].get<std::string>()) {
            std::cout << __FUNCTION__ << std::endl;
        }
        custom_class3(const std::string& str) : m_str(str) { }
        std::string to_string() const { json_type json; json["m_str"] = m_str; return json.to_string(); }
        static custom_class3* from_json(const json_type& json, custom_class3* ptr) {
            if (ptr == nullptr) {
                ptr = new custom_class3();
            }
            
            ptr->m_str = json["m_str"].get<std::string>();
            return ptr;
        }
        std::string m_str;
    };
}