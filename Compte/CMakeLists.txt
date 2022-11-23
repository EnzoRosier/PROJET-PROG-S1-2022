cmake_minimum_required (VERSION 3.9)

project(Compte)

set (CMAKE_CXX_STANDARD 17)

set(SRCS "Compte.cpp" "Compte.h")

if(MSVC)
	add_compile_options($<$<CONFIG:Release>:/MT> # Runtime library: Multi-threaded
                      $<$<CONFIG:Debug>:/MTd> # Runtime library: Multi-threaded Debug
                      )
endif(MSVC)

add_executable (mainCompte "Compte.h" "Compte.cpp" "mainCompte.cpp")


add_library (CompteLib "Compte.cpp" "Compte.h")
