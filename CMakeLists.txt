# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

project ("PROJET PROG S1 2022")


# Incluez les sous-projets.
add_subdirectory ("PROJET PROG S1 2022")
add_subdirectory ("Json")
add_subdirectory ("Compte")

add_subdirectory ("Banque")