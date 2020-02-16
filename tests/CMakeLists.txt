cmake_minimum_required(VERSION 3.5)

# 设置项目名 
set(CXX_PROJECT_NAME json)
project(${CXX_PROJECT_NAME})
 
 
if(CMAKE_BUILD_TYPE STREQUAL Release)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")  # O2
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") # using GCC  
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wl,--gc-sections")  # 空间压缩  
	endif() 
endif() 

 
#开启异常处理，将部分告警视为错误
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC") #using Visual Studio C++
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /we4013 /we4431 /we4133 /we4716 /we6244 /we6246 /we4457 /we4456 /we4172 /we4700 /we4477 /we4018 /we4047")  
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") # using GCC  
	set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}  -latomic -pthread")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -Werror=implicit-function-declaration -Werror=implicit-int  -Werror=return-type  -Werror=return-local-addr -Werror=uninitialized -Werror=format -DLINUX ")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # using Clang
	
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")# using Intel C++
	
endif()

#输出 CMAKE_CXX_FLAGS
#message ("${CXX_PROJECT_NAME} SET CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS} ") 

# 收集头文件
file(GLOB_RECURSE PROJECT_HEADERS ./*.hpp ./*.h) 

# 收集源文件
file(GLOB PROJECT_CPPS ./*.cpp)
source_group("${PROJECT_CPPS}")
source_group("${PROJECT_CPPS}" "${PROJECT_HEADERS}")
  

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") 
	set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -O2")
endif()
   
add_executable(${CXX_PROJECT_NAME}  "${PROJECT_CPPS}" "${PROJECT_HEADERS}") 
#add_executable(${CXX_PROJECT_NAME}  "json_object_utest.cpp" "main.cpp" )
#add_executable(${CXX_PROJECT_NAME}  "readme_utest.cpp" "main.cpp" )
#add_executable(${CXX_PROJECT_NAME}  "json_utest.cpp" "main.cpp" ) 
#add_executable(${CXX_PROJECT_NAME}  "json_utest2.cpp" "main.cpp" )
#add_executable(${CXX_PROJECT_NAME}  "json_constructor_utest.cpp" "main.cpp" )
#add_executable(${CXX_PROJECT_NAME}  "json_complex_utest.cpp" "main.cpp" )
#add_executable(${CXX_PROJECT_NAME}  "main.cpp" )
#add_executable(${CXX_PROJECT_NAME}  "json_pfms_utest.cpp" "main.cpp" )
#add_executable(${CXX_PROJECT_NAME}  "nlohmann.cpp" "main.cpp" )
#add_executable(${CXX_PROJECT_NAME}  "rapidjson_utest.cpp" "main.cpp" )
#add_executable(${CXX_PROJECT_NAME}  "json_pfms_utest.cpp" "rapidjson_utest.cpp"  "main.cpp" )
#add_executable(${CXX_PROJECT_NAME}  "nlohmann.cpp" "rapidjson_utest.cpp"   "json_pfms_utest.cpp" "main.cpp" )
target_compile_definitions("${PROJECT_NAME}" PRIVATE "-D AMO_USE_LITE_JSON")
target_compile_definitions("${PROJECT_NAME}" PRIVATE "-D AMO_USE_STREAM_JSON")
target_compile_definitions("${PROJECT_NAME}" PRIVATE "-D AMO_USE_STD_JSON ")

target_compile_options(${CXX_PROJECT_NAME} PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++11>)
  
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/data/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/data/" ) 