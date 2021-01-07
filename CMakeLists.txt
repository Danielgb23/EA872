# Versao minima do cmake
cmake_minimum_required(VERSION 3.0)

#gdb flag debug
set(CMAKE_BUILD_TYPE Debug)

# Nome do meu projeto
project(madrugada_dos_mortos)

add_executable(madruga src/main.cpp)

#flag pthread
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem) 

# Especificar onde estao os header files
include_directories( ${Boost_INCLUDE_DIRS} )
include_directories(include)

# Bibliotecas locais (estaticas)
add_library(entity src/model/entity.cpp)
target_link_libraries(madruga entity)

add_library(player src/model/player.cpp)

add_library(mapa src/model/mapa.cpp)
target_link_libraries(madruga mapa)

add_library(assets src/view/assets.cpp)
target_link_libraries(assets boost_filesystem)
target_link_libraries(madruga assets)

add_library(view src/view/view.cpp)
target_link_libraries(view assets)
target_link_libraries(madruga view)

add_library(net src/controller/net.cpp)

add_library(update src/controller/update.cpp)
target_link_libraries(madruga update)
target_link_libraries(update entity)
target_link_libraries(update view)
target_link_libraries(update mapa)
target_link_libraries(update net)
target_link_libraries(update assets)
target_link_libraries(update player)

add_library(INIReader src/INIReader.cpp)
target_link_libraries(madruga INIReader)
target_link_libraries(entity INIReader)

add_library(ini src/ini.c)
target_link_libraries(INIReader ini)



# Garantir que usaremos C++11 (ou superior, se preciso)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Bibliotecas linkadas externamente
target_link_libraries(madruga SDL2)
target_link_libraries(madruga SDL2_image)
target_link_libraries(update SDL2_image)
target_link_libraries(entity SDL2_image)
target_link_libraries(update SDL2_ttf)
target_link_libraries(view SDL2_ttf)
target_link_libraries(update Threads::Threads)

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


