

cmake_minimum_required(VERSION 3.17)
project(Mulit-Array VERSION 0.1.0 LANGUAGES CXX CUDA)

find_package(ArrayFire 3.7)

add_subdirectory(extern/googletest EXCLUDE_FROM_ALL)

add_library(multiarray
  include/af/context.h
  include/af/multiarray.h
  src/context.cpp
  src/multiarray.cpp
  )
target_include_directories(multiarray
  PRIVATE
  PUBLIC
    extern/threads
    include)

target_link_libraries(multiarray
    PUBLIC ArrayFire::afcuda)

add_executable(basic_test test/basic_test.cpp)
target_link_libraries(basic_test PRIVATE gtest gtest_main multiarray)
