#include <iostream>
#include <cstdint>

#include "./../json.hpp"
#include "./utest.hpp"


class JsonInfoPod : public amo::json_object<amo::json> {
public:
    JsonInfoPod() {
        memset(&m_chars[0], 0, sizeof(m_chars));
    }
    AMO_ENTITY_ARGS_GET_BEGIN(JsonInfoPod)
    AMO_ENTITY_ARGS_GET(m_bool)
    AMO_ENTITY_ARGS_GET(m_char)
    AMO_ENTITY_ARGS_GET(m_int8_t)
    AMO_ENTITY_ARGS_GET(m_int16_t)
    AMO_ENTITY_ARGS_GET(m_int32_t)
    AMO_ENTITY_ARGS_GET(m_int64_t)
    AMO_ENTITY_ARGS_GET(m_uint8_t)
    AMO_ENTITY_ARGS_GET(m_uint16_t)
    AMO_ENTITY_ARGS_GET(m_uint32_t)
    AMO_ENTITY_ARGS_GET(m_uin64_t)
    AMO_ENTITY_ARGS_GET(m_float)
    AMO_ENTITY_ARGS_GET(m_double)
    AMO_ENTITY_ARGS_GET(m_string)
    AMO_ENTITY_ARGS_GET(m_chars)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(JsonInfoPod)
    AMO_ENTITY_ARGS_SET(m_bool)
    AMO_ENTITY_ARGS_SET(m_char)
    AMO_ENTITY_ARGS_SET(m_int8_t)
    AMO_ENTITY_ARGS_SET(m_int16_t)
    AMO_ENTITY_ARGS_SET(m_int32_t)
    AMO_ENTITY_ARGS_SET(m_int64_t)
    AMO_ENTITY_ARGS_SET(m_uint8_t)
    AMO_ENTITY_ARGS_SET(m_uint16_t)
    AMO_ENTITY_ARGS_SET(m_uint32_t)
    AMO_ENTITY_ARGS_SET(m_uin64_t)
    AMO_ENTITY_ARGS_SET(m_float)
    AMO_ENTITY_ARGS_SET(m_double)
    AMO_ENTITY_ARGS_SET(m_string)
    AMO_ENTITY_ARGS_SET(m_chars)
    AMO_ENTITY_ARGS_SET_END()
    
    bool m_bool;
    char m_char;
    int8_t m_int8_t;
    int16_t m_int16_t;
    int32_t m_int32_t;
    int64_t m_int64_t;
    uint8_t m_uint8_t;
    uint16_t m_uint16_t;
    uint32_t m_uint32_t;
    uint64_t m_uin64_t;
    float m_float;;
    double m_double;
    std::string m_string;
    char m_chars[128];
};

class JsonInfoClass : public amo::json_object<amo::json> {
public:
    AMO_ENTITY_ARGS_GET_BEGIN(JsonInfoClass)
    AMO_ENTITY_ARGS_GET(m_jsoninfo1)
    AMO_ENTITY_ARGS_GET(m_jsoninfo2)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(JsonInfoClass)
    AMO_ENTITY_ARGS_SET(m_jsoninfo1)
    AMO_ENTITY_ARGS_SET(m_jsoninfo2)
    AMO_ENTITY_ARGS_SET_END()
    
    JsonInfoPod m_jsoninfo1;
    std::shared_ptr<JsonInfoPod> m_jsoninfo2;
};

namespace amo {
    // 支持二维数组
    template<> class is_container<std::vector<std::vector<int> > > {
    public:
        const static int32_t value = 1;
    };
    template<> class is_container< std::vector< std::list<  JsonInfoClass > > > {
    public:
        const static int32_t value = 1;
    };
}


class JsonInfoContainer : public amo::json_object<amo::json> {

public:
    AMO_ENTITY_ARGS_GET_BEGIN(JsonInfoContainer)
    AMO_ENTITY_ARGS_GET(vec1)
    AMO_ENTITY_ARGS_GET(vec2)
    AMO_ENTITY_ARGS_GET(vec3)
    AMO_ENTITY_ARGS_GET(m_jsoninfo2)
    AMO_ENTITY_ARGS_GET(m_jsoninfo3)
    AMO_ENTITY_ARGS_GET(m_jsoninfo4)
    AMO_ENTITY_ARGS_GET(m_jsoninfo5)
    AMO_ENTITY_ARGS_GET(m_jsoninfo6)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(JsonInfoContainer)
    AMO_ENTITY_ARGS_SET(vec1)
    AMO_ENTITY_ARGS_SET(vec2)
    AMO_ENTITY_ARGS_SET(vec3)
    AMO_ENTITY_ARGS_SET(m_jsoninfo2)
    AMO_ENTITY_ARGS_SET(m_jsoninfo3)
    AMO_ENTITY_ARGS_SET(m_jsoninfo4)
    AMO_ENTITY_ARGS_SET(m_jsoninfo5)
    AMO_ENTITY_ARGS_SET(m_jsoninfo6)
    AMO_ENTITY_ARGS_SET_END()
    
    std::deque< std::string > vec1;
    std::list< std::string > vec2;
    std::vector<std::vector<int> > vec3;
    std::shared_ptr<JsonInfoClass> m_jsoninfo2;
    JsonInfoClass m_jsoninfo3;
    std::vector< std::shared_ptr<JsonInfoClass> > m_jsoninfo4;
    std::vector< JsonInfoClass > m_jsoninfo5;
    std::vector< std::list<  JsonInfoClass > > m_jsoninfo6;
};

class JsonInfoUnknown : public amo::json_object<amo::json> {
public:
    AMO_ENTITY_ARGS_GET_BEGIN(JsonInfoUnknown)
    AMO_ENTITY_ARGS_GET(m_bool)
    AMO_ENTITY_ARGS_GET(m_char)
    AMO_ENTITY_ARGS_GET(m_int8_t)
    AMO_ENTITY_ARGS_GET(m_int16_t)
    AMO_ENTITY_ARGS_GET(m_int32_t)
    AMO_ENTITY_ARGS_GET(m_int64_t)
    AMO_ENTITY_ARGS_GET(m_uint8_t)
    AMO_ENTITY_ARGS_GET(m_uint16_t)
    AMO_ENTITY_ARGS_GET(m_uint32_t)
    AMO_ENTITY_ARGS_GET(m_uin64_t)
    AMO_ENTITY_ARGS_GET(m_float)
    AMO_ENTITY_ARGS_GET(m_double)
    AMO_ENTITY_ARGS_GET(m_string)
    AMO_ENTITY_ARGS_GET(m_smart_int)
    AMO_ENTITY_ARGS_GET(vec1)
    AMO_ENTITY_ARGS_GET(vec2)
    AMO_ENTITY_ARGS_GET(vec3)
    AMO_ENTITY_ARGS_GET(m_jsoninfo2)
    AMO_ENTITY_ARGS_GET(m_jsoninfo3)
    AMO_ENTITY_ARGS_GET(m_jsoninfo4)
    AMO_ENTITY_ARGS_GET(m_jsoninfo5)
    AMO_ENTITY_ARGS_GET(m_json)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(JsonInfoUnknown)
    AMO_ENTITY_ARGS_SET(m_bool)
    AMO_ENTITY_ARGS_SET(m_char)
    AMO_ENTITY_ARGS_SET(m_int8_t)
    AMO_ENTITY_ARGS_SET(m_int16_t)
    AMO_ENTITY_ARGS_SET(m_int32_t)
    AMO_ENTITY_ARGS_SET(m_int64_t)
    AMO_ENTITY_ARGS_SET(m_uint8_t)
    AMO_ENTITY_ARGS_SET(m_uint16_t)
    AMO_ENTITY_ARGS_SET(m_uint32_t)
    AMO_ENTITY_ARGS_SET(m_uin64_t)
    AMO_ENTITY_ARGS_SET(m_float)
    AMO_ENTITY_ARGS_SET(m_double)
    AMO_ENTITY_ARGS_SET(m_string)
    AMO_ENTITY_ARGS_SET(m_smart_int)
    AMO_ENTITY_ARGS_SET(vec1)
    AMO_ENTITY_ARGS_SET(vec2)
    AMO_ENTITY_ARGS_SET(vec3)
    AMO_ENTITY_ARGS_SET(m_jsoninfo2)
    AMO_ENTITY_ARGS_SET(m_jsoninfo3)
    AMO_ENTITY_ARGS_SET(m_jsoninfo4)
    AMO_ENTITY_ARGS_SET(m_jsoninfo5)
    AMO_ENTITY_ARGS_SET(m_json)
    AMO_ENTITY_ARGS_SET_END()
    
    bool m_bool;
    char m_char;
    int8_t m_int8_t;
    int16_t m_int16_t;
    int32_t m_int32_t;
    int64_t m_int64_t;
    uint8_t m_uint8_t;
    uint16_t m_uint16_t;
    uint32_t m_uint32_t;
    uint64_t m_uin64_t;
    float m_float;;
    double m_double;
    std::string m_string;
    
    std::shared_ptr<int32_t> m_smart_int;
    std::vector<int> vec1;
    std::vector< std::shared_ptr<int> > vec2;
    std::vector<std::vector<int> > vec3;
    std::shared_ptr<JsonInfoPod> m_jsoninfo2;
    JsonInfoPod m_jsoninfo3;
    std::vector< std::shared_ptr<JsonInfoClass> > m_jsoninfo4;
    std::vector<  JsonInfoClass> m_jsoninfo5;
    
    amo::json m_json;
};


class MyObject {
public:
    MyObject() {
        index = 0;
    }
    int32_t index;
    std::string value;
};
// 综合演示
class JsonInfoExtend : public JsonInfoUnknown {
public:
    AMO_ENTITY_ARGS_GET_BEGIN(JsonInfoExtend)
    AMO_ENTITY_ARGS_GET(m_string_2)
    
    AMO_ENTITY_ARGS_GET_EXTEND(JsonInfoUnknown)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(JsonInfoExtend)
    AMO_ENTITY_ARGS_SET(m_string_2)
    
    AMO_ENTITY_ARGS_SET_EXTEND(JsonInfoUnknown)
    AMO_ENTITY_ARGS_SET_END()
    
    virtual void on_to_json(JsonType& json) const override {
        std::string value = std::to_string(m_myObject.index) + "|" + m_myObject.value;
        json.put("m_myObject", value);
    }
    
    
    virtual void on_from_json(const JsonType& json) override {
        //std::string value = std::to_string(m_myObject.index) + "|" + m_myObject.value;
        
        if (json.contains_key("m_myObject")) {
            std::string value = json["m_myObject"];
            size_t index = value.find('|');
            
            if (index != -1) {
                std::stringstream stream;
                stream << value.substr(0, index - 0);
                stream >> m_myObject.index;
                m_myObject.value = value.substr(index + 1);
            }
        }
        
        
    }
    
    std::string m_string_2;
    MyObject m_myObject;
};

//MAKE_TYPE_TRAITS(JsonInfoPod)
//MAKE_TYPE_TRAITS(JsonInfoClass)


class JsonInfoPodLight {
    using JsonType = amo::json;
    
public:
    AMO_ENTITY_ARGS_GET_BEGIN(JsonInfoPodLight)
    AMO_ENTITY_ARGS_GET(m_bool)
    AMO_ENTITY_ARGS_GET(m_char)
    AMO_ENTITY_ARGS_GET(m_int8_t)
    AMO_ENTITY_ARGS_GET(m_int16_t)
    AMO_ENTITY_ARGS_GET(m_int32_t)
    AMO_ENTITY_ARGS_GET(m_int64_t)
    AMO_ENTITY_ARGS_GET(m_uint8_t)
    AMO_ENTITY_ARGS_GET(m_uint16_t)
    AMO_ENTITY_ARGS_GET(m_uint32_t)
    AMO_ENTITY_ARGS_GET(m_uin64_t)
    AMO_ENTITY_ARGS_GET(m_float)
    AMO_ENTITY_ARGS_GET(m_double)
    AMO_ENTITY_ARGS_GET(m_string)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(JsonInfoPodLight)
    AMO_ENTITY_ARGS_SET(m_bool)
    AMO_ENTITY_ARGS_SET(m_char)
    AMO_ENTITY_ARGS_SET(m_int8_t)
    AMO_ENTITY_ARGS_SET(m_int16_t)
    AMO_ENTITY_ARGS_SET(m_int32_t)
    AMO_ENTITY_ARGS_SET(m_int64_t)
    AMO_ENTITY_ARGS_SET(m_uint8_t)
    AMO_ENTITY_ARGS_SET(m_uint16_t)
    AMO_ENTITY_ARGS_SET(m_uint32_t)
    AMO_ENTITY_ARGS_SET(m_uin64_t)
    AMO_ENTITY_ARGS_SET(m_float)
    AMO_ENTITY_ARGS_SET(m_double)
    AMO_ENTITY_ARGS_SET(m_string)
    AMO_ENTITY_ARGS_SET_END()
    
    bool m_bool;
    char m_char;
    int8_t m_int8_t;
    int16_t m_int16_t;
    int32_t m_int32_t;
    int64_t m_int64_t;
    uint8_t m_uint8_t;
    uint16_t m_uint16_t;
    uint32_t m_uint32_t;
    uint64_t m_uin64_t;
    float m_float;;
    double m_double;
    std::string m_string;
};


class JsonInfoClassLight {
public:
    using JsonType = amo::json;
    JsonInfoClassLight() {
        m_jsoninfo3 = nullptr;
    }
public:
    AMO_ENTITY_ARGS_GET_BEGIN_WITH_JSON_CONSTRUCTOR(JsonInfoClassLight)
    AMO_ENTITY_ARGS_GET(m_jsoninfo1)
    AMO_ENTITY_ARGS_GET(m_jsoninfo2)
    
    AMO_ENTITY_ARGS_GET(m_jsoninfo3)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(JsonInfoClassLight)
    AMO_ENTITY_ARGS_SET(m_jsoninfo1)
    AMO_ENTITY_ARGS_SET(m_jsoninfo2)
    AMO_ENTITY_ARGS_SET(m_jsoninfo3)
    AMO_ENTITY_ARGS_SET_END()
    
    JsonInfoPod m_jsoninfo1;
    std::shared_ptr<JsonInfoPod> m_jsoninfo2;
    JsonInfoPod* m_jsoninfo3;
};

class JsonInfoContainerLight  {
public:
    typedef amo::json JsonType;
    
public:
    AMO_ENTITY_ARGS_GET_BEGIN(JsonInfoContainerLight)
    AMO_ENTITY_ARGS_GET(vec1)
    AMO_ENTITY_ARGS_GET(vec2)
    AMO_ENTITY_ARGS_GET(vec3)
    AMO_ENTITY_ARGS_GET(m_jsoninfo2)
    AMO_ENTITY_ARGS_GET(m_jsoninfo3)
    AMO_ENTITY_ARGS_GET(m_jsoninfo4)
    AMO_ENTITY_ARGS_GET(m_jsoninfo5)
    AMO_ENTITY_ARGS_GET(m_jsoninfo6)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(JsonInfoContainerLight)
    AMO_ENTITY_ARGS_SET(vec1)
    AMO_ENTITY_ARGS_SET(vec2)
    AMO_ENTITY_ARGS_SET(vec3)
    AMO_ENTITY_ARGS_SET(m_jsoninfo2)
    AMO_ENTITY_ARGS_SET(m_jsoninfo3)
    AMO_ENTITY_ARGS_SET(m_jsoninfo4)
    AMO_ENTITY_ARGS_SET(m_jsoninfo5)
    AMO_ENTITY_ARGS_SET(m_jsoninfo6)
    AMO_ENTITY_ARGS_SET_END()
    
    std::deque< std::string > vec1;
    std::list< std::string > vec2;
    std::vector<std::vector<int> > vec3;
    std::shared_ptr<JsonInfoClassLight> m_jsoninfo2;
    JsonInfoClass m_jsoninfo3;
    std::vector< std::shared_ptr<JsonInfoClass> > m_jsoninfo4;
    std::vector<  JsonInfoClass > m_jsoninfo5;
    std::vector< std::list<  JsonInfoClass > > m_jsoninfo6;
};

class JsonInfoUnknownLight  {
public:
    using JsonType = amo::json;
    
public:
    AMO_ENTITY_ARGS_GET_BEGIN(JsonInfoUnknownLight)
    AMO_ENTITY_ARGS_GET(m_bool)
    AMO_ENTITY_ARGS_GET(m_char)
    AMO_ENTITY_ARGS_GET(m_int8_t)
    AMO_ENTITY_ARGS_GET(m_int16_t)
    AMO_ENTITY_ARGS_GET(m_int32_t)
    AMO_ENTITY_ARGS_GET(m_int64_t)
    AMO_ENTITY_ARGS_GET(m_uint8_t)
    AMO_ENTITY_ARGS_GET(m_uint16_t)
    AMO_ENTITY_ARGS_GET(m_uint32_t)
    AMO_ENTITY_ARGS_GET(m_uin64_t)
    AMO_ENTITY_ARGS_GET(m_float)
    AMO_ENTITY_ARGS_GET(m_double)
    AMO_ENTITY_ARGS_GET(m_string)
    AMO_ENTITY_ARGS_GET(m_smart_int)
    AMO_ENTITY_ARGS_GET(vec1)
    AMO_ENTITY_ARGS_GET(vec2)
    AMO_ENTITY_ARGS_GET(vec3)
    AMO_ENTITY_ARGS_GET(m_jsoninfo2)
    AMO_ENTITY_ARGS_GET(m_jsoninfo3)
    AMO_ENTITY_ARGS_GET(m_jsoninfo4)
    AMO_ENTITY_ARGS_GET(m_jsoninfo5)
    AMO_ENTITY_ARGS_GET(m_json)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(JsonInfoUnknownLight)
    AMO_ENTITY_ARGS_SET(m_bool)
    AMO_ENTITY_ARGS_SET(m_char)
    AMO_ENTITY_ARGS_SET(m_int8_t)
    AMO_ENTITY_ARGS_SET(m_int16_t)
    AMO_ENTITY_ARGS_SET(m_int32_t)
    AMO_ENTITY_ARGS_SET(m_int64_t)
    AMO_ENTITY_ARGS_SET(m_uint8_t)
    AMO_ENTITY_ARGS_SET(m_uint16_t)
    AMO_ENTITY_ARGS_SET(m_uint32_t)
    AMO_ENTITY_ARGS_SET(m_uin64_t)
    AMO_ENTITY_ARGS_SET(m_float)
    AMO_ENTITY_ARGS_SET(m_double)
    AMO_ENTITY_ARGS_SET(m_string)
    AMO_ENTITY_ARGS_SET(m_smart_int)
    AMO_ENTITY_ARGS_SET(vec1)
    AMO_ENTITY_ARGS_SET(vec2)
    AMO_ENTITY_ARGS_SET(vec3)
    AMO_ENTITY_ARGS_SET(m_jsoninfo2)
    AMO_ENTITY_ARGS_SET(m_jsoninfo3)
    AMO_ENTITY_ARGS_SET(m_jsoninfo4)
    AMO_ENTITY_ARGS_SET(m_jsoninfo5)
    AMO_ENTITY_ARGS_SET(m_json)
    AMO_ENTITY_ARGS_SET_END()
    
    bool m_bool;
    char m_char;
    int8_t m_int8_t;
    int16_t m_int16_t;
    int32_t m_int32_t;
    int64_t m_int64_t;
    uint8_t m_uint8_t;
    uint16_t m_uint16_t;
    uint32_t m_uint32_t;
    uint64_t m_uin64_t;
    float m_float;;
    double m_double;
    std::string m_string;
    
    std::shared_ptr<int32_t> m_smart_int;
    std::vector<int> vec1;
    std::vector< std::shared_ptr<int> > vec2;
    std::vector<std::vector<int> > vec3;
    std::shared_ptr<JsonInfoPod> m_jsoninfo2;
    JsonInfoPod m_jsoninfo3;
    std::vector< std::shared_ptr<JsonInfoClass> > m_jsoninfo4;
    std::vector<  JsonInfoClass> m_jsoninfo5;
    
    amo::json m_json;
};

// 综合演示
class JsonInfoExtendLight : public JsonInfoUnknownLight {
public:
    AMO_ENTITY_ARGS_GET_BEGIN(JsonInfoExtendLight)
    AMO_ENTITY_ARGS_GET(m_string_2)
    AMO_ENTITY_ARGS_GET_CALLBACK(on_from_json)
    AMO_ENTITY_ARGS_GET_EXTEND(JsonInfoUnknownLight)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(JsonInfoExtendLight)
    AMO_ENTITY_ARGS_SET(m_string_2)
    AMO_ENTITY_ARGS_SET_CALLBACK(onToJson)
    AMO_ENTITY_ARGS_SET_EXTEND(JsonInfoUnknownLight)
    AMO_ENTITY_ARGS_SET_END()
    
    virtual void onToJson(JsonType& json) const   {
        std::string value = std::to_string(m_myObject.index) + "|" + m_myObject.value;
        json.put("m_myObject", value);
    }
    
    
    virtual void on_from_json(const JsonType& json)   {
        //std::string value = std::to_string(m_myObject.index) + "|" + m_myObject.value;
        
        if (json.contains_key("m_myObject")) {
            std::string value = json["m_myObject"];
            size_t index = value.find('|');
            
            if (index != -1) {
                std::stringstream stream;
                stream << value.substr(0, index - 0);
                stream >> m_myObject.index;
                m_myObject.value = value.substr(index + 1);
            }
        }
    }
    
    std::string m_string_2;
    MyObject m_myObject;
};

class JsonInfoExtendLight2 : public JsonInfoExtendLight {
public:
    AMO_ENTITY_ARGS_GET_BEGIN(JsonInfoExtendLight2)
    AMO_ENTITY_ARGS_GET(m_string_3)
    AMO_ENTITY_ARGS_GET_CALLBACK(on_from_json)
    AMO_ENTITY_ARGS_GET_EXTEND(JsonInfoExtendLight)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(JsonInfoExtendLight2)
    AMO_ENTITY_ARGS_SET(m_string_3)
    AMO_ENTITY_ARGS_SET_CALLBACK(onToJson)
    AMO_ENTITY_ARGS_SET_EXTEND(JsonInfoExtendLight)
    AMO_ENTITY_ARGS_SET_END()
    
    virtual void onToJson(JsonType& json) const override {
        std::string value = std::to_string(m_myObject2.index) + "|" + m_myObject2.value;
        json.put("m_myObject2", value);
        
        return JsonInfoExtendLight::onToJson(json);
    }
    
    
    virtual void on_from_json(const JsonType& json) override {
        //std::string value = std::to_string(m_myObject2.index) + "|" + m_myObject2.value;
        
        if (json.contains_key("m_myObject2")) {
            std::string value = json["m_myObject2"];
            size_t index = value.find('|');
            
            if (index != -1) {
                std::stringstream stream;
                stream << value.substr(0, index - 0);
                stream >> m_myObject2.index;
                m_myObject2.value = value.substr(index + 1);
            }
        }
        
        return JsonInfoExtendLight::on_from_json(json);
    }
    
    std::string m_string_3;
    
    MyObject m_myObject2;
};



class JsonInfoPodLight2 {
    using JsonType = amo::json;
    
public:


    bool m_bool;
    char m_char;
    int8_t m_int8_t;
    int16_t m_int16_t;
    int32_t m_int32_t;
    int64_t m_int64_t;
    uint8_t m_uint8_t;
    uint16_t m_uint16_t;
    uint32_t m_uint32_t;
    uint64_t m_uin64_t;
    float m_float;;
    double m_double;
    std::string m_string;
    
};

class JsonInfoPodLight2Ex : public JsonInfoPodLight2 {
public:
    using JsonType = amo::json;
    
    AMO_ENTITY_ARGS_GET_BEGIN(JsonInfoPodLight2Ex)
    AMO_ENTITY_ARGS_GET(m_bool)
    AMO_ENTITY_ARGS_GET(m_char)
    AMO_ENTITY_ARGS_GET(m_int8_t)
    AMO_ENTITY_ARGS_GET(m_int16_t)
    AMO_ENTITY_ARGS_GET(m_int32_t)
    AMO_ENTITY_ARGS_GET(m_int64_t)
    AMO_ENTITY_ARGS_GET(m_uint8_t)
    AMO_ENTITY_ARGS_GET(m_uint16_t)
    AMO_ENTITY_ARGS_GET(m_uint32_t)
    AMO_ENTITY_ARGS_GET(m_uin64_t)
    AMO_ENTITY_ARGS_GET(m_float)
    AMO_ENTITY_ARGS_GET(m_double)
    AMO_ENTITY_ARGS_GET(m_string)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(JsonInfoPodLight2Ex)
    AMO_ENTITY_ARGS_SET(m_bool)
    AMO_ENTITY_ARGS_SET(m_char)
    AMO_ENTITY_ARGS_SET(m_int8_t)
    AMO_ENTITY_ARGS_SET(m_int16_t)
    AMO_ENTITY_ARGS_SET(m_int32_t)
    AMO_ENTITY_ARGS_SET(m_int64_t)
    AMO_ENTITY_ARGS_SET(m_uint8_t)
    AMO_ENTITY_ARGS_SET(m_uint16_t)
    AMO_ENTITY_ARGS_SET(m_uint32_t)
    AMO_ENTITY_ARGS_SET(m_uin64_t)
    AMO_ENTITY_ARGS_SET(m_float)
    AMO_ENTITY_ARGS_SET(m_double)
    AMO_ENTITY_ARGS_SET(m_string)
    AMO_ENTITY_ARGS_SET_END()
};

//template<typename T, typename JsonType>
//static typename std::enable_if<std::is_class<T>::value, T >::type& from_json(const JsonType& json, T& ptr, bool callOnFromJson = true) {
//    std::cout << 1 << std::endl;
//    return ptr;
//}

//typedef amo::json JsonType;
//template<typename T >
//static typename std::enable_if<amo::is_smart_pointer<typename std::decay<T>::type>::value, T >::type from_json(const JsonType& json, const T& ptr = {}, bool callOnFromJson = true) {
//    std::cout << 2 << std::endl;
//    return ptr;
//}
//
//template<typename T >
//static typename std::enable_if< std::is_pointer<typename std::decay<T>::type >::value, T >::type from_json(const JsonType& json, const T& ptr = {}, bool callOnFromJson = true) {
//    std::cout << 3 << std::endl;
//    return (T)ptr;
//}

class abcc {
public:
    typedef amo::json JsonType;
public:

    AMO_ENTITY_ARGS_GET_BEGIN_WITH_DEFAULT_CONSTRUCTOR(abcc)
    AMO_ENTITY_ARGS_GET(a)
    AMO_ENTITY_ARGS_GET(d)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(abcc)
    AMO_ENTITY_ARGS_SET(a)
    AMO_ENTITY_ARGS_SET(d)
    AMO_ENTITY_ARGS_SET_END()
    
    int a;
    uint16_t d[64];
    //LittleEndianWORD d[64];
};

class abcd {
public:
    typedef amo::json JsonType;
public:
    abcd() {
        b = nullptr;
    }
    ~abcd() {
        if (b != nullptr) {
            delete b;
        }
    }
    
    abcd& operator=(const JsonType& json) {
        this->join_json(json);
        return *this;
    }
    AMO_ENTITY_ARGS_GET_BEGIN_WITH_JSON_CONSTRUCTOR(abcd)
    AMO_ENTITY_ARGS_GET(a)
    //AMO_ENTITY_ARGS_GET(b)
    AMO_ENTITY_ARGS_GET_END()
    
    AMO_ENTITY_ARGS_SET_BEGIN(abcd)
    AMO_ENTITY_ARGS_SET(a)
    //AMO_ENTITY_ARGS_SET(b)
    AMO_ENTITY_ARGS_SET_END()
    
    int a;
    int* b;
};


//MAKE_TYPE_TRAITS(abcc)

TEST(json_object, to_json_from_json) {
    amo::json json;
    abcc abc = json;
    abc = json;
    json = abc;
}

TEST(json_object, ObjectPodLightHelper) {

    amo::json json1;
    json1["a"] = 12;
    json1["b"] = 5;
    int* cc = new int[4];
    int dddd = sizeof(cc);
    int dd[3] = { 3 };
    int mm = std::is_array<int[3]>::value;
    int mm1 = std::is_array<std::decay<int[3]>::type>::value;
    int mm3 = std::is_pointer<int[3]>::value;
    abcc c11;
    //from_json<abcc, amo::json>(json1,c11);
    std::shared_ptr<abcc> c12 = abcc::from_json(json1, std::shared_ptr<abcc>());
    abcc::from_json(json1, c12);
    abcc* c13 = nullptr;
    abcc::from_json(json1, c13);
    abcc c14 = json1;
    abcd d1 = json1;
    amo::json json;
    
    json.put("m_int8_t", 23);
    json.put("m_smart_int", 22);
    json.put("m_smart_int", 22);
    
    json.put("m_bool", true);
    json.put("m_char", 'c');
    json.put("m_int8_t", 8);
    json.put("m_int16_t", 16);
    json.put("m_int32_t", 32);
    json.put("m_int64_t", 64);
    json.put("m_uint8_t", 8);
    json.put("m_uint16_t", 16);
    json.put("m_uint32_t", 32);
    json.put("m_uin64_t", 64);
    json.put("m_float", 1.0);
    json.put("m_double", 2.22);
    json.put("m_string", "string txt");
    std::shared_ptr<JsonInfoPodLight2> ptr = JsonInfoPodLight2Ex::fromJson(json);
    std::string str = std::static_pointer_cast<JsonInfoPodLight2Ex>(ptr)->to_json().to_string();
    //amo::json_object_assist<JsonInfoPodLight2, amo::json>().to_json();
    //amo::json_object_assist<JsonInfoPodLight2, amo::json>().
    EXPECT_EQ(ptr->m_bool, json["m_bool"].get<bool>());
    EXPECT_EQ(ptr->m_char, json["m_char"].get<char>());
    EXPECT_EQ(ptr->m_int8_t, json["m_int8_t"].get<int8_t>());
    EXPECT_EQ(ptr->m_int16_t, json["m_int16_t"].get<int16_t>());
    EXPECT_EQ(ptr->m_int32_t, json["m_int32_t"].get<int32_t>());
    EXPECT_EQ(ptr->m_int64_t, json["m_int64_t"].get<int64_t>());
    EXPECT_EQ(ptr->m_uint8_t, json["m_uint8_t"].get<uint8_t>());
    EXPECT_EQ(ptr->m_uint16_t, json["m_uint16_t"].get<uint16_t>());
    EXPECT_EQ(ptr->m_uint32_t, json["m_uint32_t"].get<uint32_t>());
    EXPECT_EQ(ptr->m_uin64_t, json["m_uin64_t"].get<uint64_t>());
    EXPECT_EQ(ptr->m_float, json["m_float"].get<float>());
    EXPECT_EQ(ptr->m_double, json["m_double"].get<double>());
    EXPECT_EQ(ptr->m_string, json["m_string"].get<std::string>());
}


TEST(json_object, ObjectPodLight) {

    amo::json json;
    json.put("m_int8_t", 23);
    json.put("m_smart_int", 22);
    json.put("m_smart_int", 22);
    
    json.put("m_bool", true);
    json.put("m_char", 'c');
    json.put("m_int8_t", 8);
    json.put("m_int16_t", 16);
    json.put("m_int32_t", 32);
    json.put("m_int64_t", 64);
    json.put("m_uint8_t", 8);
    json.put("m_uint16_t", 16);
    json.put("m_uint32_t", 32);
    json.put("m_uin64_t", 64);
    json.put("m_float", 1.0);
    json.put("m_double", 2.22);
    json.put("m_string", "string txt");
    
    auto ptr = JsonInfoPodLight::fromJson(json);
    EXPECT_EQ(ptr->m_bool, json["m_bool"].get<bool>());
    EXPECT_EQ(ptr->m_char, json["m_char"].get<char>());
    EXPECT_EQ(ptr->m_int8_t, json["m_int8_t"].get<int8_t>());
    EXPECT_EQ(ptr->m_int16_t, json["m_int16_t"].get<int16_t>());
    EXPECT_EQ(ptr->m_int32_t, json["m_int32_t"].get<int32_t>());
    EXPECT_EQ(ptr->m_int64_t, json["m_int64_t"].get<int64_t>());
    EXPECT_EQ(ptr->m_uint8_t, json["m_uint8_t"].get<uint8_t>());
    EXPECT_EQ(ptr->m_uint16_t, json["m_uint16_t"].get<uint16_t>());
    EXPECT_EQ(ptr->m_uint32_t, json["m_uint32_t"].get<uint32_t>());
    EXPECT_EQ(ptr->m_uin64_t, json["m_uin64_t"].get<uint64_t>());
    EXPECT_EQ(ptr->m_float, json["m_float"].get<float>());
    EXPECT_EQ(ptr->m_double, json["m_double"].get<double>());
    EXPECT_EQ(ptr->m_string, json["m_string"].get<std::string>());
}

TEST(json_object, ObjectClassLight) {
    amo::json json;
    json.put("m_int8_t", 23);
    json.put("m_smart_int", 22);
    json.put("m_smart_int", 22);
    json.put("m_bool", true);
    json.put("m_char", 'c');
    json.put("m_int8_t", 8);
    json.put("m_int16_t", 16);
    json.put("m_int32_t", 32);
    json.put("m_int64_t", 64);
    json.put("m_uint8_t", 8);
    json.put("m_uint16_t", 16);
    json.put("m_uint32_t", 32);
    json.put("m_uin64_t", 64);
    json.put("m_float", 1.0);
    json.put("m_double", 2.22);
    json.put("m_string", "string txt");
    
    amo::json info;
    info.put("m_jsoninfo1", json);
    info.put("m_jsoninfo2", json);
    info.put("m_jsoninfo3", json);
    
    auto jsonInfoClass = JsonInfoClassLight::fromJson(info);
    std::unique_ptr<JsonInfoClassLight> ptr3 = info;
    {
        auto ptr = &jsonInfoClass->m_jsoninfo1;
        EXPECT_EQ(ptr->m_bool, json["m_bool"].get<bool>());
        EXPECT_EQ(ptr->m_char, json["m_char"].get<char>());
        EXPECT_EQ(ptr->m_int8_t, json["m_int8_t"].get<int8_t>());
        EXPECT_EQ(ptr->m_int16_t, json["m_int16_t"].get<int16_t>());
        EXPECT_EQ(ptr->m_int32_t, json["m_int32_t"].get<int32_t>());
        EXPECT_EQ(ptr->m_int64_t, json["m_int64_t"].get<int64_t>());
        EXPECT_EQ(ptr->m_uint8_t, json["m_uint8_t"].get<uint8_t>());
        EXPECT_EQ(ptr->m_uint16_t, json["m_uint16_t"].get<uint16_t>());
        EXPECT_EQ(ptr->m_uint32_t, json["m_uint32_t"].get<uint32_t>());
        EXPECT_EQ(ptr->m_uin64_t, json["m_uin64_t"].get<uint64_t>());
        EXPECT_EQ(ptr->m_float, json["m_float"].get<float>());
        EXPECT_EQ(ptr->m_double, json["m_double"].get<double>());
        EXPECT_EQ(ptr->m_string, json["m_string"].get<std::string>());
    }
    {
        auto ptr = jsonInfoClass->m_jsoninfo2;
        EXPECT_EQ(ptr->m_bool, json["m_bool"].get<bool>());
        EXPECT_EQ(ptr->m_char, json["m_char"].get<char>());
        EXPECT_EQ(ptr->m_int8_t, json["m_int8_t"].get<int8_t>());
        EXPECT_EQ(ptr->m_int16_t, json["m_int16_t"].get<int16_t>());
        EXPECT_EQ(ptr->m_int32_t, json["m_int32_t"].get<int32_t>());
        EXPECT_EQ(ptr->m_int64_t, json["m_int64_t"].get<int64_t>());
        EXPECT_EQ(ptr->m_uint8_t, json["m_uint8_t"].get<uint8_t>());
        EXPECT_EQ(ptr->m_uint16_t, json["m_uint16_t"].get<uint16_t>());
        EXPECT_EQ(ptr->m_uint32_t, json["m_uint32_t"].get<uint32_t>());
        EXPECT_EQ(ptr->m_uin64_t, json["m_uin64_t"].get<uint64_t>());
        EXPECT_EQ(ptr->m_float, json["m_float"].get<float>());
        EXPECT_EQ(ptr->m_double, json["m_double"].get<double>());
        EXPECT_EQ(ptr->m_string, json["m_string"].get<std::string>());
        
    }
    
}

TEST(json_object, ObjectContainerLight) {
    amo::json vec1(amo::json_value_array);
    vec1.push_back("1");
    vec1.push_back("2");
    vec1.push_back("3");
    
    amo::json vec2(amo::json_value_array);
    vec2.push_back("4");
    vec2.push_back("5");
    vec2.push_back("6");
    
    amo::json vec3(amo::json_value_array);
    
    {
        amo::json arr3(amo::json_value_array);
        arr3.push_back(7);
        arr3.push_back(8);
        arr3.push_back(9);
        
        vec3.push_back(arr3);
        vec3.push_back(arr3);
        vec3.push_back(arr3);
        vec3.push_back(arr3);
        vec3.push_back(arr3);
        vec3.push_back(arr3);
        vec3.push_back(arr3);
    }
    
    
    amo::json json;
    json.put("vec1", vec1);
    json.put("vec2", vec2);
    json.put("vec3", vec3);
    
    
    amo::json info;
    info.put("m_bool", true);
    info.put("m_char", 'c');
    info.put("m_int8_t", 8);
    info.put("m_int16_t", 16);
    info.put("m_int32_t", 32);
    info.put("m_int64_t", 64);
    info.put("m_uint8_t", 8);
    info.put("m_uint16_t", 16);
    info.put("m_uint32_t", 32);
    info.put("m_uin64_t", 64);
    info.put("m_float", 1.0);
    info.put("m_double", 2.22);
    info.put("m_string", "string txt");
    
    json.put("m_jsoninfo2", info);
    json.put("m_jsoninfo3", info);
    
    
    amo::json jsoninfoclass;
    jsoninfoclass.put("m_jsoninfo1", info);
    jsoninfoclass.put("m_jsoninfo2", info);
    
    json.put("m_jsoninfo2", jsoninfoclass);
    json.put("m_jsoninfo3", jsoninfoclass);
    
    amo::json arr(amo::json_value_array);
    arr.push_back(jsoninfoclass);
    arr.push_back(jsoninfoclass);
    arr.push_back(jsoninfoclass);
    arr.push_back(jsoninfoclass);
    
    json.put("m_jsoninfo4", arr);
    json.put("m_jsoninfo5", arr);
    
    amo::json arr2(amo::json_value_array);
    arr2.push_back(arr);
    arr2.push_back(arr);
    arr2.push_back(arr);
    json.put("m_jsoninfo6", arr2);
    
    auto jsonInfoContainer = JsonInfoContainerLight::fromJson(json);
    
    json = info;
    
    {
        auto ptr = &jsonInfoContainer->m_jsoninfo3.m_jsoninfo1;
        EXPECT_EQ(ptr->m_bool, json["m_bool"].get<bool>());
        EXPECT_EQ(ptr->m_char, json["m_char"].get<char>());
        EXPECT_EQ(ptr->m_int8_t, json["m_int8_t"].get<int8_t>());
        EXPECT_EQ(ptr->m_int16_t, json["m_int16_t"].get<int16_t>());
        EXPECT_EQ(ptr->m_int32_t, json["m_int32_t"].get<int32_t>());
        EXPECT_EQ(ptr->m_int64_t, json["m_int64_t"].get<int64_t>());
        EXPECT_EQ(ptr->m_uint8_t, json["m_uint8_t"].get<uint8_t>());
        EXPECT_EQ(ptr->m_uint16_t, json["m_uint16_t"].get<uint16_t>());
        EXPECT_EQ(ptr->m_uint32_t, json["m_uint32_t"].get<uint32_t>());
        EXPECT_EQ(ptr->m_uin64_t, json["m_uin64_t"].get<uint64_t>());
        EXPECT_EQ(ptr->m_float, json["m_float"].get<float>());
        EXPECT_EQ(ptr->m_double, json["m_double"].get<double>());
        EXPECT_EQ(ptr->m_string, json["m_string"].get<std::string>());
        
    }
    {
        auto ptr = jsonInfoContainer->m_jsoninfo2->m_jsoninfo2;
        EXPECT_EQ(ptr->m_bool, json["m_bool"].get<bool>());
        EXPECT_EQ(ptr->m_char, json["m_char"].get<char>());
        EXPECT_EQ(ptr->m_int8_t, json["m_int8_t"].get<int8_t>());
        EXPECT_EQ(ptr->m_int16_t, json["m_int16_t"].get<int16_t>());
        EXPECT_EQ(ptr->m_int32_t, json["m_int32_t"].get<int32_t>());
        EXPECT_EQ(ptr->m_int64_t, json["m_int64_t"].get<int64_t>());
        EXPECT_EQ(ptr->m_uint8_t, json["m_uint8_t"].get<uint8_t>());
        EXPECT_EQ(ptr->m_uint16_t, json["m_uint16_t"].get<uint16_t>());
        EXPECT_EQ(ptr->m_uint32_t, json["m_uint32_t"].get<uint32_t>());
        EXPECT_EQ(ptr->m_uin64_t, json["m_uin64_t"].get<uint64_t>());
        EXPECT_EQ(ptr->m_float, json["m_float"].get<float>());
        EXPECT_EQ(ptr->m_double, json["m_double"].get<double>());
        EXPECT_EQ(ptr->m_string, json["m_string"].get<std::string>());
        
    }
    
}

TEST(json_object, ObjectUnknownLight) {

    amo::json json;
    json.put("m_int8_t", 23);
    json.put("m_smart_int", 22);
    amo::json arr(amo::json_value_array);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    amo::json arr2(amo::json_value_array);
    arr2.push_back(arr);
    arr2.push_back(arr);
    arr2.push_back(arr);
    
    json.put("vec1", arr);
    json.put("vec2", arr);
    json.put("vec3", arr2);
    amo::json jsoninfo = json;
    amo::json jsoninfoarr(amo::json_value_array);
    jsoninfoarr.push_back(jsoninfo);
    jsoninfoarr.push_back(jsoninfo);
    jsoninfoarr.push_back(jsoninfo);
    json.put("m_jsoninfo2", jsoninfo);
    json.put("m_jsoninfo3", jsoninfo);
    json.put("m_jsoninfo4", jsoninfoarr);
    json.put("m_jsoninfo5", jsoninfoarr);
    
    auto ptr = JsonInfoUnknownLight::fromJson(json);
    ptr->m_double = 11.3;
    ptr->vec1[0] = 88;
    *ptr->vec2[1] = 14;
    ptr->vec3[1][2] = 14;
    
}

TEST(json_object, JsonInfoExtendLight) {

    amo::json json;
    json.put("m_int8_t", 23);
    json.put("m_smart_int", 22);
    amo::json arr(amo::json_value_array);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    amo::json arr2(amo::json_value_array);
    arr2.push_back(arr);
    arr2.push_back(arr);
    arr2.push_back(arr);
    
    json.put("vec1", arr);
    json.put("vec2", arr);
    json.put("vec3", arr2);
    amo::json jsoninfo = json;
    amo::json jsoninfoarr(amo::json_value_array);
    jsoninfoarr.push_back(jsoninfo);
    jsoninfoarr.push_back(jsoninfo);
    jsoninfoarr.push_back(jsoninfo);
    json.put("m_jsoninfo2", jsoninfo);
    json.put("m_jsoninfo3", jsoninfo);
    json.put("m_jsoninfo4", jsoninfoarr);
    json.put("m_jsoninfo5", jsoninfoarr);
    json.put("m_myObject", "1|abcde");
    
    
    auto ptr = JsonInfoExtendLight::fromJson(json);
    EXPECT_EQ(ptr->m_myObject.index, 1);
    EXPECT_EQ(ptr->m_myObject.value, "abcde");
    
    
    ptr->m_myObject.index = 6;
    json = ptr->to_json();
    EXPECT_EQ(json["m_myObject"].get<std::string>(), "6|abcde");
}

TEST(json_object, JsonInfoExtendLight2) {

    amo::json json;
    json.put("m_int8_t", 23);
    json.put("m_smart_int", 22);
    amo::json arr(amo::json_value_array);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    amo::json arr2(amo::json_value_array);
    arr2.push_back(arr);
    arr2.push_back(arr);
    arr2.push_back(arr);
    
    json.put("vec1", arr);
    json.put("vec2", arr);
    json.put("vec3", arr2);
    amo::json jsoninfo = json;
    amo::json jsoninfoarr(amo::json_value_array);
    jsoninfoarr.push_back(jsoninfo);
    jsoninfoarr.push_back(jsoninfo);
    jsoninfoarr.push_back(jsoninfo);
    json.put("m_jsoninfo2", jsoninfo);
    json.put("m_jsoninfo3", jsoninfo);
    json.put("m_jsoninfo4", jsoninfoarr);
    json.put("m_jsoninfo5", jsoninfoarr);
    json.put("m_myObject", "1|abcde");
    json.put("m_myObject2", "2|abcde");
    
    auto ptr = JsonInfoExtendLight2::fromJson(json);
    EXPECT_EQ(ptr->m_myObject.index, 1);
    EXPECT_EQ(ptr->m_myObject.value, "abcde");
    EXPECT_EQ(ptr->m_myObject2.index, 2);
    EXPECT_EQ(ptr->m_myObject2.value, "abcde");
    
    ptr->m_myObject.index = 6;
    ptr->m_myObject2.index = 7;
    json = ptr->to_json();
    EXPECT_EQ(json["m_myObject"].get<std::string>(), "6|abcde");
    EXPECT_EQ(json["m_myObject2"].get<std::string>(), "7|abcde");
}

TEST(json_object, ObjectPod) {

    amo::json json;
    json.put("m_int8_t", 23);
    json.put("m_smart_int", 22);
    json.put("m_smart_int", 22);
    
    json.put("m_bool", true);
    json.put("m_char", 'c');
    json.put("m_int8_t", 8);
    json.put("m_int16_t", 16);
    json.put("m_int32_t", 32);
    json.put("m_int64_t", 64);
    json.put("m_uint8_t", 8);
    json.put("m_uint16_t", 16);
    json.put("m_uint32_t", 32);
    json.put("m_uin64_t", 64);
    json.put("m_float", 1.0);
    json.put("m_double", 2.22);
    json.put("m_string", "string txt");
    
    auto ptr = JsonInfoPod::fromJson(json);
    EXPECT_EQ(ptr->m_bool, json["m_bool"].get<bool>());
    EXPECT_EQ(ptr->m_char, json["m_char"].get<char>());
    EXPECT_EQ(ptr->m_int8_t, json["m_int8_t"].get<int8_t>());
    EXPECT_EQ(ptr->m_int16_t, json["m_int16_t"].get<int16_t>());
    EXPECT_EQ(ptr->m_int32_t, json["m_int32_t"].get<int32_t>());
    EXPECT_EQ(ptr->m_int64_t, json["m_int64_t"].get<int64_t>());
    EXPECT_EQ(ptr->m_uint8_t, json["m_uint8_t"].get<uint8_t>());
    EXPECT_EQ(ptr->m_uint16_t, json["m_uint16_t"].get<uint16_t>());
    EXPECT_EQ(ptr->m_uint32_t, json["m_uint32_t"].get<uint32_t>());
    EXPECT_EQ(ptr->m_uin64_t, json["m_uin64_t"].get<uint64_t>());
    EXPECT_EQ(ptr->m_float, json["m_float"].get<float>());
    EXPECT_EQ(ptr->m_double, json["m_double"].get<double>());
    EXPECT_EQ(ptr->m_string, json["m_string"].get<std::string>());
}

TEST(json_object, ObjectClass) {


    amo::json json;
    json.put("m_int8_t", 23);
    json.put("m_smart_int", 22);
    json.put("m_smart_int", 22);
    
    json.put("m_bool", true);
    json.put("m_char", 'c');
    json.put("m_int8_t", 8);
    json.put("m_int16_t", 16);
    json.put("m_int32_t", 32);
    json.put("m_int64_t", 64);
    json.put("m_uint8_t", 8);
    json.put("m_uint16_t", 16);
    json.put("m_uint32_t", 32);
    json.put("m_uin64_t", 64);
    json.put("m_float", 1.0);
    json.put("m_double", 2.22);
    json.put("m_string", "string txt");
    
    amo::json info;
    info.put("m_jsoninfo1", json);
    info.put("m_jsoninfo2", json);
    
    auto jsonInfoClass = JsonInfoClass::fromJson(info);
    {
        auto ptr = &jsonInfoClass->m_jsoninfo1;
        EXPECT_EQ(ptr->m_bool, json["m_bool"].get<bool>());
        EXPECT_EQ(ptr->m_char, json["m_char"].get<char>());
        EXPECT_EQ(ptr->m_int8_t, json["m_int8_t"].get<int8_t>());
        EXPECT_EQ(ptr->m_int16_t, json["m_int16_t"].get<int16_t>());
        EXPECT_EQ(ptr->m_int32_t, json["m_int32_t"].get<int32_t>());
        EXPECT_EQ(ptr->m_int64_t, json["m_int64_t"].get<int64_t>());
        EXPECT_EQ(ptr->m_uint8_t, json["m_uint8_t"].get<uint8_t>());
        EXPECT_EQ(ptr->m_uint16_t, json["m_uint16_t"].get<uint16_t>());
        EXPECT_EQ(ptr->m_uint32_t, json["m_uint32_t"].get<uint32_t>());
        EXPECT_EQ(ptr->m_uin64_t, json["m_uin64_t"].get<uint64_t>());
        EXPECT_EQ(ptr->m_float, json["m_float"].get<float>());
        EXPECT_EQ(ptr->m_double, json["m_double"].get<double>());
        EXPECT_EQ(ptr->m_string, json["m_string"].get<std::string>());
    }
    {
        auto ptr = jsonInfoClass->m_jsoninfo2;
        EXPECT_EQ(ptr->m_bool, json["m_bool"].get<bool>());
        EXPECT_EQ(ptr->m_char, json["m_char"].get<char>());
        EXPECT_EQ(ptr->m_int8_t, json["m_int8_t"].get<int8_t>());
        EXPECT_EQ(ptr->m_int16_t, json["m_int16_t"].get<int16_t>());
        EXPECT_EQ(ptr->m_int32_t, json["m_int32_t"].get<int32_t>());
        EXPECT_EQ(ptr->m_int64_t, json["m_int64_t"].get<int64_t>());
        EXPECT_EQ(ptr->m_uint8_t, json["m_uint8_t"].get<uint8_t>());
        EXPECT_EQ(ptr->m_uint16_t, json["m_uint16_t"].get<uint16_t>());
        EXPECT_EQ(ptr->m_uint32_t, json["m_uint32_t"].get<uint32_t>());
        EXPECT_EQ(ptr->m_uin64_t, json["m_uin64_t"].get<uint64_t>());
        EXPECT_EQ(ptr->m_float, json["m_float"].get<float>());
        EXPECT_EQ(ptr->m_double, json["m_double"].get<double>());
        EXPECT_EQ(ptr->m_string, json["m_string"].get<std::string>());
        
    }
    
}

TEST(json_object, ObjectContainer) {


    amo::json vec1(amo::json_value_array);
    vec1.push_back("1");
    vec1.push_back("2");
    vec1.push_back("3");
    
    amo::json vec2(amo::json_value_array);
    vec2.push_back("4");
    vec2.push_back("5");
    vec2.push_back("6");
    
    amo::json vec3(amo::json_value_array);
    
    {
        amo::json arr3(amo::json_value_array);
        arr3.push_back(7);
        arr3.push_back(8);
        arr3.push_back(9);
        
        
        vec3.push_back(arr3);
        vec3.push_back(arr3);
        vec3.push_back(arr3);
        vec3.push_back(arr3);
        vec3.push_back(arr3);
        vec3.push_back(arr3);
        vec3.push_back(arr3);
        
    }
    
    
    amo::json json;
    json.put("vec1", vec1);
    json.put("vec2", vec2);
    json.put("vec3", vec3);
    
    
    amo::json info;
    info.put("m_bool", true);
    info.put("m_char", 'c');
    info.put("m_int8_t", 8);
    info.put("m_int16_t", 16);
    info.put("m_int32_t", 32);
    info.put("m_int64_t", 64);
    info.put("m_uint8_t", 8);
    info.put("m_uint16_t", 16);
    info.put("m_uint32_t", 32);
    info.put("m_uin64_t", 64);
    info.put("m_float", 1.0);
    info.put("m_double", 2.22);
    info.put("m_string", "string txt");
    
    json.put("m_jsoninfo2", info);
    json.put("m_jsoninfo3", info);
    
    
    amo::json jsoninfoclass;
    jsoninfoclass.put("m_jsoninfo1", info);
    jsoninfoclass.put("m_jsoninfo2", info);
    
    json.put("m_jsoninfo2", jsoninfoclass);
    json.put("m_jsoninfo3", jsoninfoclass);
    
    amo::json arr(amo::json_value_array);
    arr.push_back(jsoninfoclass);
    arr.push_back(jsoninfoclass);
    arr.push_back(jsoninfoclass);
    arr.push_back(jsoninfoclass);
    
    json.put("m_jsoninfo4", arr);
    json.put("m_jsoninfo5", arr);
    
    amo::json arr2(amo::json_value_array);
    arr2.push_back(arr);
    arr2.push_back(arr);
    arr2.push_back(arr);
    json.put("m_jsoninfo6", arr2);
    
    
    
    
    
    
    auto jsonInfoContainer = JsonInfoContainer::fromJson(json);
    
    json = info;
    
    {
        auto ptr = &jsonInfoContainer->m_jsoninfo3.m_jsoninfo1;
        EXPECT_EQ(ptr->m_bool, json["m_bool"].get<bool>());
        EXPECT_EQ(ptr->m_char, json["m_char"].get<char>());
        EXPECT_EQ(ptr->m_int8_t, json["m_int8_t"].get<int8_t>());
        EXPECT_EQ(ptr->m_int16_t, json["m_int16_t"].get<int16_t>());
        EXPECT_EQ(ptr->m_int32_t, json["m_int32_t"].get<int32_t>());
        EXPECT_EQ(ptr->m_int64_t, json["m_int64_t"].get<int64_t>());
        EXPECT_EQ(ptr->m_uint8_t, json["m_uint8_t"].get<uint8_t>());
        EXPECT_EQ(ptr->m_uint16_t, json["m_uint16_t"].get<uint16_t>());
        EXPECT_EQ(ptr->m_uint32_t, json["m_uint32_t"].get<uint32_t>());
        EXPECT_EQ(ptr->m_uin64_t, json["m_uin64_t"].get<uint64_t>());
        EXPECT_EQ(ptr->m_float, json["m_float"].get<float>());
        EXPECT_EQ(ptr->m_double, json["m_double"].get<double>());
        EXPECT_EQ(ptr->m_string, json["m_string"].get<std::string>());
        
    }
    {
        auto ptr = jsonInfoContainer->m_jsoninfo2->m_jsoninfo2;
        EXPECT_EQ(ptr->m_bool, json["m_bool"].get<bool>());
        EXPECT_EQ(ptr->m_char, json["m_char"].get<char>());
        EXPECT_EQ(ptr->m_int8_t, json["m_int8_t"].get<int8_t>());
        EXPECT_EQ(ptr->m_int16_t, json["m_int16_t"].get<int16_t>());
        EXPECT_EQ(ptr->m_int32_t, json["m_int32_t"].get<int32_t>());
        EXPECT_EQ(ptr->m_int64_t, json["m_int64_t"].get<int64_t>());
        EXPECT_EQ(ptr->m_uint8_t, json["m_uint8_t"].get<uint8_t>());
        EXPECT_EQ(ptr->m_uint16_t, json["m_uint16_t"].get<uint16_t>());
        EXPECT_EQ(ptr->m_uint32_t, json["m_uint32_t"].get<uint32_t>());
        EXPECT_EQ(ptr->m_uin64_t, json["m_uin64_t"].get<uint64_t>());
        EXPECT_EQ(ptr->m_float, json["m_float"].get<float>());
        EXPECT_EQ(ptr->m_double, json["m_double"].get<double>());
        EXPECT_EQ(ptr->m_string, json["m_string"].get<std::string>());
        
    }
    
}

TEST(json_object, ObjectUnknown) {

    amo::json json;
    json.put("m_int8_t", 23);
    json.put("m_smart_int", 22);
    amo::json arr(amo::json_value_array);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    amo::json arr2(amo::json_value_array);
    arr2.push_back(arr);
    arr2.push_back(arr);
    arr2.push_back(arr);
    
    json.put("vec1", arr);
    json.put("vec2", arr);
    json.put("vec3", arr2);
    amo::json jsoninfo = json;
    amo::json jsoninfoarr(amo::json_value_array);
    jsoninfoarr.push_back(jsoninfo);
    jsoninfoarr.push_back(jsoninfo);
    jsoninfoarr.push_back(jsoninfo);
    json.put("m_jsoninfo2", jsoninfo);
    json.put("m_jsoninfo3", jsoninfo);
    json.put("m_jsoninfo4", jsoninfoarr);
    json.put("m_jsoninfo5", jsoninfoarr);
    
    auto ptr = JsonInfoUnknown::fromJson(json);
    ptr->m_double = 11.3;
    ptr->vec1[0] = 88;
    *ptr->vec2[1] = 14;
    ptr->vec3[1][2] = 14;
    
}

TEST(json_object, JsonInfoExtend) {
    amo::json json;
    json.put("m_int8_t", 23);
    json.put("m_smart_int", 22);
    amo::json arr(amo::json_value_array);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    amo::json arr2(amo::json_value_array);
    arr2.push_back(arr);
    arr2.push_back(arr);
    arr2.push_back(arr);
    
    json.put("vec1", arr);
    json.put("vec2", arr);
    json.put("vec3", arr2);
    amo::json jsoninfo = json;
    amo::json jsoninfoarr(amo::json_value_array);
    jsoninfoarr.push_back(jsoninfo);
    jsoninfoarr.push_back(jsoninfo);
    jsoninfoarr.push_back(jsoninfo);
    json.put("m_jsoninfo2", jsoninfo);
    json.put("m_jsoninfo3", jsoninfo);
    json.put("m_jsoninfo4", jsoninfoarr);
    json.put("m_jsoninfo5", jsoninfoarr);
    json.put("m_myObject", "1|abcde");
    
    
    auto ptr = JsonInfoExtend::fromJson(json);
    EXPECT_EQ(ptr->m_myObject.index, 1);
    EXPECT_EQ(ptr->m_myObject.value, "abcde");
    
    
    ptr->m_myObject.index = 6;
    json = ptr->to_json();
    EXPECT_EQ(json["m_myObject"].get<std::string>(), "6|abcde");
}