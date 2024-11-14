cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(MORPION_IA)

# Définir les sources
set(SOURCES1 morpion_base/main_game.cpp IA_part/IA_Qlearning.cpp morpion_base/tab_morpion.cpp)
set(SOURCES2 IA_part/main_training.cpp IA_part/IA_Qlearning.cpp morpion_base/tab_morpion.cpp)

# Faire l'exécutable
add_executable(MORPION_GAME_IA ${SOURCES1})
add_executable(IA_TRAINING ${SOURCES2})