cmake_minimum_required (VERSION 3.9)

project(Banque)

set (CMAKE_CXX_STANDARD 17)

set(SRCS "Banque.cpp")

add_executable (banqueMain "Banque.h" "Banque.cpp" "mainBanque.cpp")

add_library (Banque ${SRCS})
target_include_directories (Banque PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
