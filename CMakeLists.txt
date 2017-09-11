cmake_minimum_required(VERSION 2.8.12)
project(trie)

set(trie_SRCS
src/trie.cpp)

add_library(trie STATIC ${trie_SRCS})
target_include_directories(trie PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(trie PUBLIC -std=c++11)
