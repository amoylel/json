// Created by amoylel on 16/02/2020.
// Copyright (c) 2020 amoylel All rights reserved.

#ifndef _UTEST_E8D8B6B5_4878_4B8E_819C_EB6CB2E1F8B8_HPP__
#define _UTEST_E8D8B6B5_4878_4B8E_819C_EB6CB2E1F8B8_HPP__

#ifndef IMPORTS_E9E128A3_ACAB_4104_A179_D834401F6B11
#define IMPORTS_E9E128A3_ACAB_4104_A179_D834401F6B11
//////////////////////////////////////////////////////////////////////////
///!@import begin
///!@import segment_macro_namespaces
///!@import segment_utest

#ifndef segment_macro_namespaces
#define segment_macro_namespaces

#ifndef _AMO_NAMESPACE_BEGIN
#define _AMO_NAMESPACE_BEGIN namespace amo {
#endif

#ifndef _AMO_NAMESPACE_END
#define _AMO_NAMESPACE_END }
#endif

#ifndef _AMO
#define _AMO ::amo::
#endif

///!@segment update timestamp 20200216124257
#endif //segment_macro_namespaces


#ifndef segment_utest
#define segment_utest

#pragma warning(push)
#pragma warning(disable:4018)

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif // _WIN32

#include <stdint.h>
#include <vector>
#include <string>
#include <memory>
#include <regex>
#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <chrono>
#include <sstream>



#define UTEST_TEST(case_name, test_name)\
    static void utest_##case_name##test_name(bool& utest_passed);\
    static std::function<void(bool&)> utest_fn##case_name##test_name = _AMO testing::utest::get_instance()->add_test(#case_name, #test_name, [](bool& passed)->void {utest_##case_name##test_name(passed);} );\
    static void utest_##case_name##test_name(bool& utest_passed)

#if !UTEST_DONT_DEFINE_TEST
# define TEST(case_name, test_name) UTEST_TEST(case_name, test_name)
#endif

#define EXPECT_COMPARE(...) \
    {int line_ = __LINE__; std::string filename_ = __FILE__;\
        try {\
            _AMO testing::compare(__VA_ARGS__);\
        }\
        catch (const _AMO testing::uexception& uexcpt) {\
            utest_passed = false;\
            _AMO testing::print_error("[    ERROR ] ") << uexcpt.to_string() << std::endl;\
        }\
        catch (const std::exception& stdexcpt) {\
            _AMO testing::print_error("[    THROW ] ") << std::string("[") + filename_ + "(" + std::to_string(line_) + ")] " + stdexcpt.what() << std::endl;\
            utest_passed = false;\
        }\
        catch (...) {\
            _AMO testing::print_error("[    THROW1 ] ") << std::endl;\
            utest_passed = false;\
        }}

#define EXPECT_EQ(...) EXPECT_COMPARE("EXPECT_EQ", utest_passed, 0, __FILE__, __LINE__, #__VA_ARGS__, ##__VA_ARGS__)
#define EXPECT_NE(...) EXPECT_COMPARE("EXPECT_NE", utest_passed,  1, __FILE__, __LINE__, #__VA_ARGS__, ##__VA_ARGS__)
#define EXPECT_GT(...) EXPECT_COMPARE("EXPECT_GT", utest_passed, 2, __FILE__, __LINE__, #__VA_ARGS__, ##__VA_ARGS__)
#define EXPECT_LT(...) EXPECT_COMPARE("EXPECT_LT", utest_passed,  3, __FILE__, __LINE__, #__VA_ARGS__, ##__VA_ARGS__)
#define EXPECT_GE(...) EXPECT_COMPARE("EXPECT_GE", utest_passed, 4, __FILE__, __LINE__, #__VA_ARGS__, ##__VA_ARGS__)
#define EXPECT_LE(...) EXPECT_COMPARE("EXPECT_LE", utest_passed, 5, __FILE__, __LINE__, #__VA_ARGS__, ##__VA_ARGS__)
#define EXPECT_TRUE(...) EXPECT_COMPARE("EXPECT_TRUE", utest_passed,  1, __FILE__, __LINE__, #__VA_ARGS__, ##__VA_ARGS__)
#define EXPECT_FALSE(...) EXPECT_COMPARE("EXPECT_TRUE", utest_passed,  0, __FILE__, __LINE__, #__VA_ARGS__, ##__VA_ARGS__)
#define CHECK(...) EXPECT_TRUE(##__VA_ARGS__)


_AMO_NAMESPACE_BEGIN
namespace testing {
    static int64_t now() {
        return std::chrono::duration_cast<std::chrono::microseconds>
               (std::chrono::system_clock::now().time_since_epoch()).count();
    }
    
#ifdef _WIN32
    static int32_t red_color()  {
        return FOREGROUND_RED | FOREGROUND_INTENSITY;
    }
    static int32_t green_color() {
        return FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    }
    static int32_t blue_color() {
        return FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    }
    static std::ostream& output_string(const std::string& str, int32_t color) {
        HANDLE m_console_handle;
        m_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO console_info;
        GetConsoleScreenBufferInfo(m_console_handle, &console_info);
        int32_t last_color = console_info.wAttributes;
        SetConsoleTextAttribute(m_console_handle, 0x0F & color | 0xf0 & console_info.wAttributes);
        std::cout << str;
        // 还原
        SetConsoleTextAttribute(m_console_handle, last_color);
        return std::cout;
    }
#else
    static inline int32_t red_color() { return 0; }
    static inline int32_t blue_color() { return 1;  }
    static inline int32_t green_color() {  return 2; }
    
    static std::ostream& output_string(const std::string& str, int32_t color) {
        const std::string  ANSI_COLOR_NORMAL_ = "\x1b[0m";
        const std::string  ANSI_COLOR_RED_ = "\x1b[31m";
        const std::string  ANSI_COLOR_GREEN_ = "\x1b[32m";
        const std::string  ANSI_COLOR_BLUE_ = "\x1b[33m";
    
        switch (color) {
            case 0:
                std::cout << ANSI_COLOR_RED_;
                break;
    
            case 1:
                std::cout << ANSI_COLOR_BLUE_;
                break;
    
            case 2:
                std::cout << ANSI_COLOR_GREEN_;
                break;
    
            default:
                break;
        }
    
        std::cout << str << ANSI_COLOR_NORMAL_;
        return std::cout;
    }
    
#endif
    static std::ostream& print_success(const std::string& str) {
        return output_string(str, green_color());
    }
    
    static std::ostream& print_error(const std::string& str) {
        return output_string(str, red_color());
    }
    
    class uexception  {
    public:
        uexception(): m_line(0) {}
        virtual ~uexception() noexcept {}
        
        uexception(const std::string& filename_, int32_t line_, const std::string& msg_) : m_filename(filename_),
            m_line(line_), m_msg(msg_)  {}
        std::string to_string() const {
            return std::string("[") + m_filename + "(" + std::to_string(m_line) + ")] " + this->what();
        }
        virtual char const* what() const   {
            return m_msg.c_str();
        }
    public:
        std::string m_filename;
        int32_t m_line;
        std::string m_msg;
    };
    
    class uparam {
    public:
        uparam() : passed_tests(0), failed_tests(0), skipped_tests(0), total_tests(0) {}
        
        void init(int argc, char** argv) {
            init_help(argc, argv);
            init_utest_filter(argc, argv);
            init_utest_list_tests(argc, argv);
            init_utest_repeat(argc, argv);
        }
        
        bool passed() const { return (passed_tests + skipped_tests == total_tests); }
        
        void init_help(int argc, char** argv) {
            std::string __help = "--help";
            
            for (int i = 1; i < argc; ++i) {
                std::string args = argv[i];
                
                if (args == __help) {
                    m_help.reset(new std::string(args.substr(0, __help.size())));
                }
            }
        }
        
        void init_utest_filter(int argc, char** argv) {
            std::string __utest_filter = "--utest_filter=";
            
            for (int i = 1; i < argc; ++i) {
                std::string args = argv[i];
                
                if (args.substr(0, __utest_filter.size()) == __utest_filter) {
                    m_utest_filter.reset(new std::string(args.substr(__utest_filter.size())));
                }
            }
            
            if (m_utest_filter) {
                try {
                    m_utest_filter_reg.reset(new std::regex(*m_utest_filter));
                } catch (const std::exception& e) {
                    m_utest_filter.reset();
                    m_utest_filter_reg.reset();
                    std::cerr << e.what() << std::endl;
                }
            }
        }
        
        void init_utest_list_tests(int argc, char** argv) {
            std::string __utest_list_tests = "--utest_list_tests";
            
            for (int i = 1; i < argc; ++i) {
                std::string args = argv[i];
                
                if (args.substr(0, __utest_list_tests.size()) == __utest_list_tests) {
                    m_utest_list_tests.reset(new std::string(args.substr(0, __utest_list_tests.size())));
                    
                    if (std::regex_match(args, std::regex(__utest_list_tests + "=.+$"))) {
                        try {
                            m_utest_list_tests_reg.reset(new std::regex(args.substr(__utest_list_tests.size() + 1)));
                        } catch (const std::exception& e) {
                            m_utest_list_tests.reset();
                            m_utest_list_tests_reg.reset();
                            std::cerr << e.what() << std::endl;
                        }
                    }
                }
            }
            
        }
        
        void init_utest_repeat(int argc, char** argv) {
            std::string __utest_repeat = "--utest_repeat=";
            
            for (int i = 1; i < argc; ++i) {
                std::string args = argv[i];
                
                if (args.substr(0, __utest_repeat.size()) == __utest_repeat) {
                    std::string repeat = args.substr(__utest_repeat.size());
                    m_utest_repeat.reset(new int(std::atoi(repeat.c_str())));
                }
            }
            
        }
        
        std::shared_ptr<std::string> m_help;
        std::shared_ptr<std::string> m_utest_filter;
        std::shared_ptr<std::regex>  m_utest_filter_reg;
        std::shared_ptr<std::string> m_utest_list_tests;
        std::shared_ptr<std::regex>  m_utest_list_tests_reg;
        std::shared_ptr<int32_t>     m_utest_repeat;
        
        std::size_t passed_tests  = 0;
        std::size_t failed_tests  = 0;
        std::size_t skipped_tests = 0;
        std::size_t total_tests   = 0;
        
    };
    class test {
    public:
        typedef  std::function<void(bool&)> test_func_type;
    public:
        test(): m_passed(true) {}
        test(test_func_type fn_) : m_fn(fn_), m_passed(true) {}
        
        int run() {
            try {
                if (m_fn) {  m_fn(m_passed); }
            } catch (const std::exception& e) {
                _AMO testing::print_error("[    THROW ] ") << e.what() << std::endl;
                m_passed = false;
            } catch (...) {
                _AMO testing::print_error("[    THROW ] ")   << std::endl;
                m_passed = false;
            }
            
            return m_passed ? 1 : 0;
        }
        
        bool passed() const { return m_passed; }
    private:
        bool            m_passed;
        test_func_type  m_fn;
    };
    
    class ucase {
    public:
        ucase(const std::string& caseName_) : caseName(caseName_) {}
        void add_test(const std::string testName, test::test_func_type testFn) {
            m_cases.push_back({ testName, test(testFn) });
        }
        
        void run(std::shared_ptr<uparam>& param) {
        
            bool print_case_info = false;
            //print_success("[----------] ") << m_cases.size() << " tests from " << caseName << std::endl;
            int64_t start_time = _AMO testing::now();
            
            for (auto& p : m_cases) {
                ++param->total_tests;
                
                if (param->m_utest_filter_reg) {
                
                    if (!std::regex_match(caseName + "." + p.first, *param->m_utest_filter_reg)) {
                        ++param->skipped_tests;
                        continue;
                    }
                    
                }
                
                int64_t test_start_time = _AMO testing::now();
                
                if (!print_case_info) {
                    print_case_info = true;
                    print_success("[----------] ") << m_cases.size() << " tests from " << caseName << std::endl;
                }
                print_success("[ RUN      ] ") << caseName << "." << p.first << std::endl;
                
                if (p.second.run() == 0) {
                    print_error("[   FAILED ] ");
                    ++param->failed_tests;
                } else {
                    print_success("[       OK ] ");
                    ++param->passed_tests;
                    
                }
                
                std::cout << caseName << "." << p.first
                          << " (" << (_AMO testing::now() - test_start_time) / 1000.0 << " ms)" << std::endl;
            }
            if (print_case_info) {
                print_success("[----------] ") << m_cases.size() << " tests from " << caseName
                                               << " (" << (_AMO testing::now() - start_time) / 1000.0 << " ms total) "
                                               << std::endl << std::endl;
            }
        }
        
        
        void list_cases() {  for (auto& p : m_cases) { std::cout << "    " << p.first << std::endl; } }
        
        std::size_t size() const { return m_cases.size(); }
        
        void list_failed_tests() {
            for (auto& p : m_cases) {
                if (!p.second.passed()) {
                    print_error("[   FAILED ] ") << caseName << "." << p.first << std::endl;
                }
            }
        }
        
    public:
        std::string caseName;
        std::vector<std::pair<std::string, test > > m_cases;
    };
    
    class utest {
    public:
        static std::shared_ptr<utest> get_instance() {
            static std::shared_ptr<utest> test(new utest());
            return test;
        }
        
        utest() {  m_param.reset(new uparam()); }
        
        void init(int argc, char** argv) {
            try {
                m_param->init(argc, argv);
            } catch (const std::exception&) {
                std::cout << "following command line flags to control its behavior:" << std::endl << std::endl;
                print_help_msg();
            }
        }
        
        test::test_func_type add_test(const std::string& caseName, const std::string& testName, test::test_func_type testFn) {
            utest::get_instance()->find_case(caseName)->add_test(testName, testFn);
            return testFn;
        }
        
        
        std::shared_ptr<ucase> find_case(const std::string& caseName) {
            auto iter = m_cases.find(caseName);
            
            if (iter == m_cases.end()) {
                iter = m_cases.insert({ caseName, std::make_shared<ucase>(caseName) }).first;
            }
            
            return iter->second;
        }
        
        // list all test cases
        void list_tests() {
            for (auto& p : m_cases) {
                if (m_param->m_utest_list_tests_reg) {
                    if (std::regex_match(p.first, *m_param->m_utest_list_tests_reg)) {
                        std::cout << p.first << "." << std::endl;
                        p.second->list_cases();
                        std::cout << std::endl;
                    }
                } else {
                    std::cout << p.first << "." << std::endl;
                    p.second->list_cases();
                    std::cout << std::endl;
                }
            }
        }
        
        // print help message
        void print_help_msg() {
        
            std::cout << "Help:" << std::endl;
            output_string("  --help", green_color()) << std::endl;
            std::cout << "      Print help message." << std::endl;
            
            std::cout << std::endl;
            
            std::cout << "Test Selection:" << std::endl;
            output_string("  --utest_list_tests", green_color()) << std::endl;
            std::cout << "      List the names of all tests instead of running them. The name of" << std::endl;
            std::cout << "      TEST(Foo, Bar) is \"Foo.Bar\"." << std::endl;
            
            output_string("  --utest_list_tests=regex", green_color()) << std::endl;
            std::cout << "      list only the tests whose name matches one of the positive patterns" << std::endl;
            std::cout << "      eg: --utest_filter=Foo or --utest_filter=Fo.+ to list test \"Foo\"." << std::endl;
            
            output_string("  --utest_filter=regex", green_color()) << std::endl;
            std::cout << "      Run only the tests whose name matches one of the positive patterns" << std::endl;
            std::cout << "      eg: --utest_filter=Foo.Bar or --utest_filter=Foo.B.+ to run test \"Foo.Bar\"." << std::endl;
            
            std::cout << std::endl;
            
            std::cout << "Test Execution:" << std::endl;
            output_string("  --utest_repeat=", green_color());
            output_string("[COUNT]", blue_color()) << std::endl;
            std::cout << "      Run the tests repeatedly; use a negative count to repeat forever." << std::endl;
            
        }
        
        void run() {
            if (m_param->m_help) {
                print_help_msg();
                return;
            }
            
            if (m_param->m_utest_list_tests) {
                list_tests();
                return;
            }
            
            
            if (m_param->m_utest_filter) {
                output_string("Note: Unit Test filter = ", blue_color());
                output_string(m_param->m_utest_filter->c_str(), red_color()) << std::endl;
            }
            
            if (m_param->m_utest_repeat && *m_param->m_utest_repeat > 1) {
                std::vector<int64_t> vec;
                
                for (int i = 0; i < *m_param->m_utest_repeat; ++i) {
                    int64_t start_t = now();
                    std::cout << "\nRepeating all tests (iteration " << i + 1 << ") . . ." << std::endl << std::endl;
                    run_once();
                    vec.push_back(now() - start_t);
                }
                
                std::sort(vec.begin(), vec.end(), [](const int64_t& a, const int64_t& b)->bool {return a > b; });
                int64_t total = 0;
                
                for (auto& p : vec) {
                    total += p;
                }
                
                print_success("\n[   REPEAT ] ") << " repeat " << *m_param->m_utest_repeat << " times, "
                                                 << "total(" << total / 1000.0 << " ms), "
                                                 << "avg(" << total / vec.size() / 1000.0 << " ms), "
                                                 << "max(" << *vec.begin() / 1000.0 << " ms), "
                                                 << "min(" << *vec.rbegin() / 1000.0 << " ms)"
                                                 << std::endl;
            } else {
                run_once();
            }
        }
        
        // running a test program
        void run_once() {
            int64_t start_time = _AMO testing::now();
            
            print_success("[==========] ") << "Running " /*<< m_param->total_tests*/
                                           << "* tests from " << m_cases.size() << " test cases. " << std::endl;
            print_success("[----------] ") << "Global test environment set-up." << std::endl;
            std::cout << std::endl;
            
            for (auto& p : m_cases) {
                p.second->run(m_param);
            }
            
            print_success("[----------] ") << "Global test environment tear-down." << std::endl;
            print_success("[==========] ")
                    << m_param->total_tests << " tests from " << m_cases.size() << " ran. "
                    << " (" << (_AMO testing::now() - start_time) / 1000.0 << " ms total) " << std::endl;
            print_success("[   PASSED ] ") << m_param->passed_tests << " tests." << std::endl;
            
            if (m_param->skipped_tests > 0) {
                print_success("[  SKIPPED ] ") << m_param->skipped_tests << " tests." << std::endl;
            }
            
            if (!m_param->passed()) {
                print_error("[   FAILED ] ") << m_param->failed_tests << " test, listed below:" << std::endl;
                
                for (auto& p : m_cases) {
                    p.second->list_failed_tests();
                }
            }
            m_param->skipped_tests = 0;
            m_param->passed_tests = 0;
            m_param->failed_tests = 0;
            m_param->total_tests = 0;
            return;
        }
    public:
        std::map<std::string, std::shared_ptr<ucase> > m_cases;
        std::shared_ptr<uparam> m_param;
    };
    
    static void run(int argc, char** argv) {
        utest::get_instance()->init(argc, argv);
        utest::get_instance()->run();
    }
    
    
    template<typename T, typename P> inline bool compare(const T& lhs, const P& rhs, int type_) {
        switch (type_) {
            case 0: // ==
                return (lhs == rhs);
                
            case 1: // !=
                return (lhs != rhs);
                
            case 2: // >
                return (lhs > rhs);
                
            case 3: // <
                return (lhs < rhs);
                
            case  4: // >=
            
                return (lhs >= rhs);
                
            case 5: // <=
                return (lhs <= rhs);
                
            default:
                return false;
        }
    }
    
    template<typename T, typename P>
    inline void compare(const std::string& prefix, bool& utest_passed, int type_, const std::string& filename_, int line_,
                        const std::string& str, const T& lhs, const P& rhs) {
                        
        try {
            if (!_AMO testing::compare(lhs, rhs, type_)) {
                std::stringstream msg_;
                msg_ << "expected: ";
                msg_ << prefix << "(" << str << "),";
                msg_ << " actual:" << lhs << " vs " << rhs;
                throw _AMO testing::uexception(filename_, line_, msg_.str());
            }
        } catch (const _AMO testing::uexception& e) {
            utest_passed = false;
            _AMO testing::print_error("[    ERROR ] ") << e.to_string() << std::endl;
        } catch (const std::exception& e) {
            utest_passed = false;
            _AMO testing::print_error("[    THROW ] ")
                    << std::string("[") + filename_ + "(" + std::to_string(line_) + ")] " + e.what() << std::endl;
        }
        
    }
    inline void compare(const std::string& prefix, bool& utest_passed, int type_, const std::string& filename_, int line_,
                        const std::string& str,
                        bool result) {
                        
        try {
            if ((type_) != (result ? 1 : 0)) {
                std::stringstream msg_;
                msg_ << "expected: ";
                msg_ << prefix << "(" << str << "),";
                msg_ << " actual:" << (result ? "true" : "false");
                std::cout <<  msg_.str() << std::endl;
                throw _AMO testing::uexception(filename_, line_, str);
            }
        } catch (const _AMO testing::uexception& e) {
            utest_passed = false;
            _AMO testing::print_error("[    ERROR ] ") << e.to_string() << std::endl;
        } catch (const std::exception& e) {
            utest_passed = false;
            _AMO testing::print_error("[    THROW ] ")
                    << std::string("[") + filename_ + "(" + std::to_string(line_) + ")] " + e.what() << std::endl;
        }
    }
}
_AMO_NAMESPACE_END

#pragma warning(pop)
///!@segment update timestamp 20200216124257
#endif //segment_utest

///!@import end
//////////////////////////////////////////////////////////////////////////
#endif // IMPORTS_E9E128A3_ACAB_4104_A179_D834401F6B11


#endif //_UTEST_E8D8B6B5_4878_4B8E_819C_EB6CB2E1F8B8_HPP__
