cmake_minimum_required (VERSION 3.9)

project(Compte)

set (CMAKE_CXX_STANDARD 17)

set(SRCS "Compte.cpp" "Compte.h")

add_executable (mainCompte "Compte.h" "Compte.cpp" "mainCompte.cpp")


add_library (CompteLib "Compte.cpp" "Compte.h")
target_include_directories (CompteLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
