cmake_minimum_required(VERSION 3.6)
project(DSA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp vector/vector.cpp vector/vector.h list/list.cpp list/list.h utils/compare_utils.h stack/stack.h stack/stack_func.cpp utils/digit_utils.h queue/queue.h)
add_executable(DSA ${SOURCE_FILES} vector/vector.cpp vector/vector.h list/list.cpp list/list.h utils/compare_utils.h stack/stack.h stack/stack_func.cpp utils/digit_utils.h queue/queue.h)