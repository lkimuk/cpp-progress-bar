cmake_minimum_required(VERSION 3.15)
project(test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test examples/test.cpp)

target_include_directories(test PRIVATE include external/aopcxx/include)
