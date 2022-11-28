cmake_minimum_required (VERSION 3.9)

project(Compte)

set (CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_RELEASE_LIBS ON)

if(MSVC)
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_options($<$<CONFIG:Release>:/MT> # Runtime library: Multi-threaded
                      $<$<CONFIG:Debug>:/MTd> # Runtime library: Multi-threaded Debug
                      )
    #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:libcpmtd /NODEFAULTLIB")
    set(Boost_USE_STATIC_RUNTIME ON)
	set(Boost_DIR "C:/tools/Boost/lib/cmake/Boost-1.80.0")

elseif(MSVC)
    set(Boost_DIR /usr/local/lib/cmake/Boost-1.80.0)
endif (MSVC)

find_package(Boost 1.80.0 COMPONENTS json serialization REQUIRED)


add_executable (mainCompte "Compte.cpp" "mainCompte.cpp")
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries (mainCompte LINK_PUBLIC ${Boost_LIBRARIES})
add_library (CompteLib "Compte.cpp")
