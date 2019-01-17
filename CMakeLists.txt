cmake_minimum_required(VERSION 2.8.12)
project(trie)
option(ENABLE_TRIE_TESTS "Enable building test program for trie" ON)
set(trie_SRCS
src/trie.cpp)

add_library(trie STATIC ${trie_SRCS})
target_include_directories(trie PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(trie PUBLIC -std=c++11)

if (ENABLE_TRIE_TESTS)
    add_executable(test_trie src/test_trie.cpp)
    target_link_libraries(test_trie trie)
endif()

