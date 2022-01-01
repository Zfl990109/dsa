cmake_minimum_required(VERSION 3.6)
project(DSA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp vector/vector.cpp vector/vector.h list/list.cpp list/list.h utils/compare_utils.h stack/stack.h stack/stack_func.cpp utils/digit_utils.h queue/queue.h queue/queue_func.cpp binary_tree/binary_tree.cpp binary_tree/binary_tree.h binary_tree/bin_node.cpp binary_tree/bin_node.h binary_tree/huffman_tree.cpp bitmap/bitmap.cpp bitmap/bitmap.h)
add_executable(DSA ${SOURCE_FILES} vector/vector.cpp vector/vector.h list/list.cpp list/list.h utils/compare_utils.h stack/stack.h stack/stack_func.cpp utils/digit_utils.h queue/queue.h queue/queue_func.cpp binary_tree/binary_tree.cpp binary_tree/binary_tree.h binary_tree/bin_node.cpp binary_tree/bin_node.h binary_tree/huffman_tree.cpp bitmap/bitmap.cpp bitmap/bitmap.h)