cmake_minimum_required (VERSION 3.9)

project(Client)

set (CMAKE_CXX_STANDARD 17)

if(MSVC)
	add_compile_options($<$<CONFIG:Release>:/MT> # Runtime library: Multi-threaded
                      $<$<CONFIG:Debug>:/MTd> # Runtime library: Multi-threaded Debug
                      )
endif(MSVC)

add_executable (mainClient "Test_client.cpp" "Client.cpp")

add_library(ClientLib "Client.cpp" "Client.h")

target_link_libraries (mainClient LINK_PUBLIC CompteLib UtilityFunctionLib)
target_link_libraries (ClientLib LINK_PUBLIC CompteLib)
