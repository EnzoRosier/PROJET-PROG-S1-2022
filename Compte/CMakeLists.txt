cmake_minimum_required (VERSION 3.9)

project(Compte)

set (CMAKE_CXX_STANDARD 17)

set(SRCS "Compte.cpp")

add_executable (mainCompte "Compte.h" "Compte.cpp" "mainCompte.cpp")

add_library (Compte ${SRCS})
target_include_directories (Compte PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
