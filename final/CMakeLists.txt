cmake_minimum_required(VERSION 3.13)
project(pljit)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
find_package(Threads REQUIRED)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_REQUIRED_FLAGS "-pthread")
include(Infrastructure)

add_subdirectory(pljit)
add_subdirectory(test)
target_link_libraries(pljit PUBLIC Threads::Threads)
