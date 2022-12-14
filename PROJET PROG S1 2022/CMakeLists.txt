# CMakeList.txt : projet CMake pour PROJET PROG S1 2022, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)
# Ajoutez une source à l'exécutable de ce projet.

# TODO: Ajoutez des tests et installez des cibles si nécessaire.

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

find_package(Boost 1.80.0 COMPONENTS system thread regex serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(ThreadFunctionLib ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
add_library(UtilityFunctionLib "Fonctions/Transaction.cpp" "Fonctions/Def_id.cpp")
target_link_libraries (UtilityFunctionLib LINK_PUBLIC BanqueLib)

add_library(ThreadFunctionLib "Fonctions/EpargneThread.cpp" "Fonctions/saveJsonthread.cpp" "Fonctions/updateThread.cpp")
target_link_libraries (ThreadFunctionLib LINK_PUBLIC BanqueLib JsonLib ${Boost_LIBRARIES})