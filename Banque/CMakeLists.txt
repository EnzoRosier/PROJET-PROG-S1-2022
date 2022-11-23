cmake_minimum_required (VERSION 3.9)

project(Banque)

set (CMAKE_CXX_STANDARD 17)

add_executable (mainBanque "mainBanque.cpp" "Banque.h" "Banque.cpp")

add_library(BanqueLib "Banque.h" "Banque.cpp")
target_link_libraries (mainBanque LINK_PUBLIC ClientLib UtilityFunctionLib)
target_link_libraries (BanqueLib LINK_PUBLIC ClientLib UtilityFunctionLib)