#include "./../json.hpp"


#include "./utest.hpp"
#include "./make_json.hpp"


TEST(json_pfms, empty_t) {
    json_type json = {};
    json = 3;
    char* ch = nullptr;
    json = ch;
    json = nullptr;
    char b[4] = { '1', '2', '4', '\0' };
    json = {};
    
    json = b;
    json = "123";
    std::cout << json.to_string() << std::endl;
}
TEST(json_pfms, testss) {
    std::cout << sizeof(amo::json::iterator) << std::endl;
    std::cout << sizeof(amo::json::iterator::MapIter) << std::endl;
    std::cout << sizeof(amo::json::iterator::ArrayIter) << std::endl;
    std::cout << sizeof(amo::json::iterator::JsonAllocType) << std::endl;
    std::cout << sizeof(std::map<std::string, amo::json::ObjectType>::iterator) << std::endl;
    std::cout << sizeof(amo::json) << std::endl;
    std::string str = make_json2().to_string();
    const char* data = str.c_str();
    const char* end = data + str.size();
    int count = 0;
    for (; data < end;) {
        if (*data++ == '\"') {
            ++count;
        }
    }
    char mm[sizeof(size_t)] = { '\"', '\"', '\"', '\"' };
    size_t mask = *(size_t*)&mm;
    
    std::cout << count << std::endl;
    std::cout << str << std::endl;
    auto bmd = 1111111111111111111111111111111111111111111111111111111111111111.32;
    auto dd = 5e-325;
    std::cout << dd << std::endl;
    std::cout << -(std::numeric_limits<double>::max)() << std::endl;
    std::cout << (std::numeric_limits<double>::min)() << std::endl;
    json_type json = amo::string_reader{ "-10.222e30" };
    json_type json1 = amo::string_reader{ "-123456789012345678901234567890" };
    json_type json2 = amo::string_reader{ "[17533471656824599138,7661509727033825881]" };
    
}
TEST(json_pfms, testss2) {

    std::string str = make_json2().to_string();
    const char* data = str.c_str();
    const char* end = data + str.size();
    int count = 0;
    char mm[sizeof(size_t)] = { '\"', '\"', '\"', '\"' };
    size_t mask = *(size_t*)&mm;
    size_t n1 = '\"';
    size_t n2 = '\"' << 8;
    size_t n3 = '\"' << 8;
    size_t n4 = '\"' << 8;
    
    for (; data < end; data += 4) {
        size_t tmp = (*(size_t*)data);
        size_t m = tmp & mask;
        switch (m) {
            case '\"':
            case '\"'<<8:
            case '\"' << 16:
            case '\"' << 24:
                ++count;
                break;
            case 0:
                break;
        }
    }
    
    
    
}
class MMM {

    char a[256];
};
TEST(json_pfms, mem0) {
    size_t index = 0;
    typedef MMM DataType;
    DataType* p;
    
    for (int i = 0; i < 100; ++i) {
        amo::json::JsonAllocType allocator(new amo::json::MemoryAllocType());
        for (int j = 0; j < 56045; ++j) {
            p = new (allocator->allocate(sizeof(DataType)))DataType();
            if (p != nullptr) {
                index++;
            }
        }
    }
    std::cout << index << std::endl;
}
TEST(json_pfms, mem0_g0) {
    size_t index = 0;
    typedef MMM DataType;
    
    for (int i = 0; i < 100; ++i) {
        DataType* p = new DataType();
        const static int MM_LEN = 256;
        std::vector<char> vec(60000 * MM_LEN);
        char* ptr = vec.data();
        //amo::json::JsonAllocType allocator(new amo::json::MemoryAllocType());
        for (int j = 0; j < 56045; ++j) {
            //memcpy(ptr, p, MM_LEN);
            p = (DataType*)ptr;// new (ptr)DataType();
            ptr += MM_LEN;
            if (p != nullptr) {
                index++;
            }
        }
    }
    std::cout << index << std::endl;
}

TEST(json_pfms, mem0_g) {
    size_t index = 0;
    typedef MMM DataType;
    
    
    for (int i = 0; i < 100; ++i) {
        DataType* p = new DataType();
        const static int MM_LEN = 256;
        std::vector<char> vec(60000 * MM_LEN);
        char* ptr = vec.data();
        //amo::json::JsonAllocType allocator(new amo::json::MemoryAllocType());
        for (int j = 0; j < 56045; ++j) {
            memcpy(ptr, p, MM_LEN);
            p = (DataType*)ptr;// new (ptr)DataType();
            
            ptr += MM_LEN;
            if (p != nullptr) {
                index++;
            }
        }
    }
    std::cout << index << std::endl;
}

TEST(json_pfms, mem) {
    size_t index = 0;
    typedef amo::json::ObjectType DataType;
    DataType* p;
    
    for (int i = 0; i < 100 ; ++i) {
        amo::json::JsonAllocType allocator(new amo::json::MemoryAllocType());
        for (int j = 0; j < 56045 * 16; ++j) {
            p = new (allocator->allocate(sizeof(DataType)))DataType();
            if (p != nullptr) {
                index++;
            }
        }
    }
    std::cout << index << std::endl;
}
TEST(json_pfms, mem1) {
    size_t index = 0;
    typedef int64_t DataType;
    DataType* p;
    
    for (int i = 0; i < 100; ++i) {
        amo::json::JsonAllocType allocator(new amo::json::MemoryAllocType());
        for (int j = 0; j < 56045 * 16; ++j) {
            p = new (allocator->allocate(sizeof(DataType)))DataType();
            if (p != nullptr) {
                index++;
            }
        }
    }
    std::cout << index << std::endl;
}
TEST(json_pfms, mem2) {
    size_t index = 0;
    typedef amo::json::ObjectType::ArrayType DataType;
    DataType* p;
    
    for (int i = 0; i < 100; ++i) {
        amo::json::JsonAllocType allocator(new amo::json::MemoryAllocType());
        //allocator->reallocate(1024 * 1024 * 120);
        for (int j = 0; j < 56045; ++j) {
            p =  new (allocator->allocate(sizeof(DataType)))DataType(allocator);
            if (p != nullptr) {
                index++;
            }
        }
    }
    std::cout << index << std::endl;
}
TEST(json_pfms, mem3) {
    size_t index = 0;
    typedef amo::json::ObjectType::ArrayType DataType;
    DataType* p;
    
    for (int i = 0; i < 100; ++i) {
        amo::json::JsonAllocType allocator(new amo::json::MemoryAllocType());
        allocator->reallocate(1024 * 1024 * 120);
        for (int j = 0; j < 56045; ++j) {
            p = new (allocator->allocate(sizeof(DataType)))DataType(allocator);
            if (p != nullptr) {
                index++;
            }
        }
    }
    std::cout << index << std::endl;
}

TEST(json_pfms, canada0) {
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

TEST(json_pfms, canada_1) {
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
        json_type json = amo::string_reader{ str };
    }
    
}
TEST(json_pfms, canada) {
    for (int i = 0; i < 100; ++i) {
        std::string filename = "./data/nativejson-benchmark/canada.json";
        json_type json = amo::file_reader{ filename };
    }
}
TEST(json_pfms, canada2) {
    for (int i = 0; i < 100; ++i) {
        std::string filename = "./data/nativejson-benchmark/canada.json";
        amo::stream::json json = amo::file_reader{ filename };
    }
}

TEST(json_pfms, citm_catalog) {
    for (int i = 0; i < 100; ++i) {
        std::string filename = "./data/nativejson-benchmark/citm_catalog.json";
        json_type json = amo::file_reader{ filename };
    }
}

TEST(json_pfms, twitter_1) {
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
    //std::cout << str.size() << std::endl;
    
    for (int i = 0; i < 100; ++i) {
        json_type json = amo::string_reader{ str };
    }
}
TEST(json_pfms, twitter) {
    for (int i = 0; i < 100; ++i) {
        std::string filename = "./data/nativejson-benchmark/twitter.json";
        json_type json = amo::file_reader{ filename };
    }
}


TEST(json_pfms, to_file) {
    json_type json1 = ::make_json();
    json_type arr(amo::json_value_array);
    
    for (int i = 0; i < length * 1; ++i) {
        arr.push_back(json1);
    }
    
    arr.to_file("./bigstr.json");
}


TEST(json_pfms, from_string_normal2) {
    json_type json = make_json2();
    std::string str = json.to_string();
    
    for (int32_t i = 0; i < length; ++i) {
        json_type json2(amo::string_reader{ str });
    }
}

TEST(json_pfms, from_string) {
    json_type json = make_json();
    std::string str = json.to_string();
    
    for (int32_t i = 0; i < length; ++i) {
        json_type json2(amo::string_reader{ str });
    }
}

TEST(json_pfms, from_string_normal) {
    json_type json = make_json();
    std::string str = json.to_string();
    
    for (int32_t i = 0; i < length; ++i) {
        json_type json2(amo::string_reader{ str });
    }
}

#ifdef AMO_USE_LITE_JSON
TEST(json_pfms, from_string_lite) {
    json_type json2 = make_json();
    std::string str = json2.to_string();
    
    for (int32_t i = 0; i < length; ++i) {
        amo::lite::json json(amo::string_reader{ str });
    }
}
#endif

#ifdef AMO_USE_STREAM_JSON
TEST(json_pfms, from_string_stream) {
    json_type json = make_json();
    std::string str = json.to_string();
    
    //std::cout << str << std::endl;
    for (int32_t i = 0; i < length; ++i) {
        amo::stream::json json2(amo::string_reader{ str });
        
        if (i == 0) {
            //std::cout << json2.to_string() << std::endl;
        }
    }
}
#endif

#ifdef AMO_USE_STD_JSON
TEST(json_pfms, from_string_stl) {
    json_type json = make_json();
    std::string str = json.to_string();
    
    for (int32_t i = 0; i < length; ++i) {
        amo::stl::json json2(amo::string_reader{ str });
        /*if (i == 0) {
            std::cout << json2.to_string() << std::endl;
        }*/
    }
}
#endif

TEST(json_pfms, to_string) {
    json_type json = make_json();
    std::size_t size = 0;
    
    for (int32_t i = 0; i < length; ++i) {
        size += json.to_string(0).size();
    }
    
    std::cout << size << std::endl;
}

TEST(json_pfms, to_string1) {
    json_type json = make_json();
    std::size_t size = 0;
    
    for (int32_t i = 0; i < length; ++i) {
        size += json.to_string(4).size();
    }
    
    std::cout << size << std::endl;
}

#include <thread>
#include <chrono>

TEST(json_pfms, from_file) {
    std::ifstream ifs("./bigstr.json", std::ios::in | std::ios::binary);
    json_type json(ifs);
    std::cout << "parse end......................." << std::endl;;
    //std::this_thread::sleep_for(std::chrono::seconds(20));
}

#ifdef AMO_USE_STREAM_JSON

TEST(json_pfms, from_file2) {
    std::ifstream ifs("./bigstr.json", std::ios::in | std::ios::binary);
    amo::stream::json json(ifs);
}

#endif

static std::string ssss111;
TEST(json_pfms, from_file3) {
    std::ifstream ifs("./bigstr.json", std::ios::in | std::ios::binary);
    std::string str;
    const int len = 65535;
    char buffer[len] = { 0 };
    
    while (!ifs.eof()) {
        ifs.read(buffer, len);
        size_t gcount = static_cast<size_t>(ifs.gcount());
        str += std::string(buffer, gcount);
    }
    
    ssss111 = str;
    std::cout << str.size() << std::endl;
    //std::shared_ptr< std::ostream> ofs(new std::fstream("./bigstr3.json", std::ios::out | std::ios::binary));
    //json.to_string(ofs);
    
}

TEST(json_pfms, from_file4) {
    json_type json(amo::string_reader{ ssss111 });
    std::cout << json.size() << std::endl;
}


TEST(json_pfms, bool_object_test) {
    json_type json;
    json.set_object();
    
    for (int i = 0; i < length * 2; ++i) {
        json[std::to_string(i)] = (false);
    }
    
    for (int i = 0; i < length * 2; ++i) {
        json[std::to_string(i)] = (i % 2 == 0);
    }
}
TEST(json_pfms, bool_object_test2) {
    json_type json;
    json.set_object();
    
    for (int i = 0; i < length * 2; ++i) {
        json[std::to_string(i)] = (false);
    }
    
    for (int i = 0; i < length * 2; ++i) {
        json.find(std::to_string(i)).set_value(i % 2 == 0, json.get_allocator());
    }
}



TEST(json_pfms, int_object_test) {
    json_type json;
    json.set_object();
    
    for (int i = 0; i < length * 2; ++i) {
        json[std::to_string(i)] = 1;
    }
    
    for (int i = 0; i < length * 2; ++i) {
        json[std::to_string(i)] = i;
    }
}
TEST(json_pfms, int_object_test2) {
    json_type json;
    json.set_object();
    
    for (int i = 0; i < length * 2; ++i) {
        json[std::to_string(i)] = 1;
    }
    
    for (int i = 0; i < length * 2; ++i) {
        json.find(std::to_string(i)).set_value(i, json.get_allocator());
    }
}


TEST(json_pfms, double_object_test) {
    json_type json;
    json.set_object();
    
    for (int i = 0; i < length * 2; ++i) {
        json[std::to_string(i)] = 1.0;
    }
    
    for (int i = 0; i < length * 2; ++i) {
        json[std::to_string(i)] = i * 1.0;
    }
}
TEST(json_pfms, double_object_test2) {
    json_type json;
    json.set_object();
    
    for (int i = 0; i < length * 2; ++i) {
        json[std::to_string(i)] = 1.0;
    }
    
    for (int i = 0; i < length * 2; ++i) {
        json.find(std::to_string(i)).set_value(i * 1.0, json.get_allocator());
    }
}



TEST(json_pfms, string_object_test) {
    json_type json;
    json.set_object();
    const std::string node = "1.0";
    
    for (int i = 0; i < length * 2; ++i) {
        json[std::to_string(i)] = node;
    }
    
    for (int i = 0; i < length * 2; ++i) {
        json[std::to_string(i)] = std::to_string(i * 1.0);
    }
}
TEST(json_pfms, string_object_test2) {
    json_type json;
    json.set_object();
    const std::string node = "1.0";
    
    for (int i = 0; i < length * 2; ++i) {
        json[std::to_string(i)] = node;
    }
    
    for (int i = 0; i < length * 2; ++i) {
        json.find(std::to_string(i)).set_value(std::to_string(i * 1.0), json.get_allocator());
    }
}


TEST(json_pfms, bool_array_test) {
    json_type json;
    json.set_array();
    
    for (int i = 0; i < length * 100; ++i) {
        json.push_back(false);
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json[i] = (i % 2 == 0);
    }
}

TEST(json_pfms, bool_array_test2) {
    json_type json;
    json.set_array(length * 100);
    
    for (int i = 0; i < length * 100; ++i) {
        json.push_back(false);
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json[i] = (i % 2 == 0);
    }
}

TEST(json_pfms, bool_array_test3) {
    json_type json;
    json.set_array();
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(-1).set_value(false, json.get_allocator());
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(i).set_value(i % 2 == 0, json.get_allocator());
    }
}

TEST(json_pfms, bool_array_test4) {
    json_type json;
    json.set_array(length * 100);
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(-1).set_value(false, json.get_allocator());
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(i).set_value(i % 2 == 0, json.get_allocator());
    }
}

TEST(json_pfms, int_array_test) {
    json_type json;
    json.set_array();
    
    for (int i = 0; i < length * 100; ++i) {
        json.push_back(555);
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json[i] = i;
    }
}
TEST(json_pfms, int_array_test1) {
    json_type json;
    json.set_array();
    
    for (int i = 0; i < length * 100; ++i) {
        json.push_back(555);
    }
    int index = 0;
    /* for (auto& p : json) {
         if (p.is<int>()) {
             ++index;
         }
     }*/
    std::cout << index << std::endl;
}
TEST(json_pfms, int_array_test2) {
    json_type json;
    json.set_array(length * 100);
    
    for (int i = 0; i < length * 100; ++i) {
        json.push_back(555);
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json[i] = i;
    }
}
TEST(json_pfms, int_array_test3) {
    json_type json;
    json.set_array();
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(-1).set_value(555, json.get_allocator());
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(i).set_value(i, json.get_allocator());
    }
}

TEST(json_pfms, int_array_test4) {
    json_type json;
    json.set_array(length * 100);
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(-1).set_value(555, json.get_allocator());
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(i).set_value(i, json.get_allocator());
    }
}


TEST(json_pfms, double_array_test) {
    json_type json;
    json.set_array();
    
    for (int i = 0; i < length * 100; ++i) {
        json.push_back(555.0);
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json[i] = i * 1.0;
    }
}
TEST(json_pfms, double_array_test2) {
    json_type json;
    json.set_array(length * 100);
    
    for (int i = 0; i < length * 100; ++i) {
        json.push_back(555.0);
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json[i] = i * 1.0;
    }
}
TEST(json_pfms, double_array_test3) {
    json_type json;
    json.set_array();
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(-1).set_value(555.0, json.get_allocator());
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(i).set_value(i * 1.0, json.get_allocator());
    }
}

TEST(json_pfms, double_array_test4) {
    json_type json;
    json.set_array(length * 100);
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(-1).set_value(555.0, json.get_allocator());
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(i).set_value(i * 1.0, json.get_allocator());
    }
}



TEST(json_pfms, string_array_test) {
    json_type json;
    json.set_array();
    
    for (int i = 0; i < length * 100; ++i) {
        json.push_back("555.0");
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json[i] = std::to_string(i * 1.0);
    }
}
TEST(json_pfms, string_array_test2) {
    json_type json;
    json.set_array(length * 100);
    
    for (int i = 0; i < length * 100; ++i) {
        json.push_back("555.0");
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json[i] = std::to_string(i * 1.0);
    }
}
TEST(json_pfms, string_array_test3) {
    json_type json;
    json.set_array();
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(-1).set_value("555.0", 5, json.get_allocator());
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(i).set_value(std::to_string(i * 1.0), json.get_allocator());
    }
}

TEST(json_pfms, string_array_test4) {
    json_type json;
    json.set_array(length * 100);
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(-1).set_value("555.0", 5, json.get_allocator());
    }
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(i).set_value(std::to_string(i * 1.0), json.get_allocator());
    }
}

TEST(json_pfms, string_array_test5) {
    json_type json;
    json.set_array(length * 100);
    
    for (int i = 0; i < length * 100; ++i) {
        json.find(-1).set_value("555.0123456789", 14, json.get_allocator());
    }
    
    for (size_t index = 0; index < 1; ++index) {
        for (int i = 0; i < length * 100; ++i) {
            std::string&& str = std::to_string(i * 1.0);
            json.find(i).set_value(str.c_str(), str.size(), json.get_allocator());
        }
    }
}
