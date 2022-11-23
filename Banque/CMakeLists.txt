cmake_minimum_required (VERSION 3.9)

project(Banque)

set (CMAKE_CXX_STANDARD 17)

if(MSVC)
	add_compile_options($<$<CONFIG:Release>:/MT> # Runtime library: Multi-threaded
                      $<$<CONFIG:Debug>:/MTd> # Runtime library: Multi-threaded Debug
                      )
endif(MSVC)

add_executable (mainBanque "mainBanque.cpp" "Banque.h" "Banque.cpp")

add_library(BanqueLib "Banque.h" "Banque.cpp")
target_link_libraries (mainBanque LINK_PUBLIC ClientLib UtilityFunctionLib)
