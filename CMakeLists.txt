# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

PROJECT(all)


# Incluez les sous-projets.
add_subdirectory ("PROJET PROG S1 2022")
add_subdirectory (Json)
add_subdirectory (Compte)
add_subdirectory ("Sockets")

add_subdirectory (Banque)
add_subdirectory (Client)
add_subdirectory (myapp)
add_subdirectory (customer)
