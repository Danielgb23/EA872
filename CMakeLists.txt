# Versao minima do cmake
cmake_minimum_required(VERSION 3.0)

#gdb flag debug
set(CMAKE_BUILD_TYPE Debug)

# Nome do meu projeto
project(madrugada_dos_mortos)

#
add_executable(madruga src/main.cpp)

# Especificar onde estao os header files
include_directories(include)

# Bibliotecas locais (estaticas)
add_library(player src/model/player.cpp)
target_link_libraries(madruga player)

add_library(view src/view/view.cpp)
target_link_libraries(madruga view)

add_library(INIReader src/INIReader.cpp)
target_link_libraries(madruga INIReader)
target_link_libraries(player INIReader)

add_library(ini src/ini.c)
target_link_libraries(INIReader ini)

#add_library(monster src/model/monster.cpp)
#target_link_libraries(madruga monster)

#add_library(monster src/model/monster.cpp)
#target_link_libraries(madruga monster)

#add_library(update src/controller/update.cpp)
#target_link_libraries(madruga update)

#add_library(controller src/controller.cpp)
#target_link_libraries(madruga controller)

# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Bibliotecas linkadas externamente
target_link_libraries(madruga SDL2)
target_link_libraries(madruga SDL2_image)

# Automatizacao do Doxygen
find_package(Doxygen REQUIRED dot)

set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_EXTRACT_PRIVATE YES)
set(DOXYGEN EXTRACT_STATIC YES)
set(DOXYGEN_TEMPLATE_RELATIONS YES)
set(DOXYGEN_COLLABORATION_GRAPH YES)
set(DOXYGEN_UML_LOOK YES)
set(DOXYGEN_CLASS_GRAPH YES)

doxygen_add_docs(doc)

