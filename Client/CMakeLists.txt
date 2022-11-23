cmake_minimum_required (VERSION 3.9)

project(Client)

set (CMAKE_CXX_STANDARD 17)

set(SRCS "Client.cpp")

add_executable (Client "Test_client.cpp" "Client.h")
include_directories(Compte)

target_link_libraries (Client LINK_PUBLIC CompteLib)

