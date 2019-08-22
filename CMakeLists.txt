
cmake_minimum_required(VERSION 2.8)

project (ldaemon )

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if (COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif (COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else ()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif ()
add_definitions("-O0 -Wall -g -ggdb") 
 
set(EXECUTABLE_OUTPUT_PATH ${ldaemon_SOURCE_DIR}/bin) 

link_directories(/usr/lib)
link_directories(/usr/lib64/mysql) 
include_directories(${ldaemon_SOURCE_DIR}/src) 
include_directories(${ldaemon_SOURCE_DIR}/include)  
aux_source_directory(./src source_code)   
add_executable(ldaemon ${source_code})
target_link_libraries(ldaemon) 
