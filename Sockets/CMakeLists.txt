cmake_minimum_required(VERSION 3.20)

project(Socket)


set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_RELEASE_LIBS ON)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    set(Boost_USE_STATIC_RUNTIME ON)
    add_compile_options($<$<CONFIG:Release>:/MT> # Runtime library: Multi-threaded
                      $<$<CONFIG:Debug>:/MTd> # Runtime library: Multi-threaded Debug
                      )
    set(Boost_DIR "C:/tools/Boost/lib/cmake/Boost-1.80.0")
elseif(MSVC)
    set(Boost_DIR /usr/local/lib/cmake/Boost-1.80.0)
endif (MSVC)

find_package(Boost 1.80.0 COMPONENTS system thread regex serialization REQUIRED)
include_directories(socket_decentralisee ${Boost_INCLUDE_DIRS})
include_directories(socket_centrale ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_executable(socket_decentralisee "banque_decentralisee.cpp" )
add_executable(socket_centrale "banque_centrale.cpp")

add_library(toolsSocketLib "tools.cpp")

target_link_libraries(socket_decentralisee LINK_PUBLIC ClientLib BanqueLib CompteLib toolsSocketLib JsonLib UtilityFunctionLib)
target_link_libraries(socket_centrale LINK_PUBLIC ClientLib BanqueLib CompteLib toolsSocketLib JsonLib ThreadFunctionLib)

