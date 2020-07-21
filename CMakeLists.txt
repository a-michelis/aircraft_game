##########################################################
# Basic Variables ########################################
##########################################################

set(PROJECT_NAME "aircraft_game")

set(SOURCE_FILES
        main.cpp
        lib/structs.h

        lib/glModel/glModel.cpp
        lib/glModel/glModel.h

        lib/gameEngine/gameEngine.cpp
        lib/gameEngine/gameEngine.h

        lib/BMPLoader/BMPLoader.cpp
        lib/BMPLoader/BMPLoader.h

        lib/callbacks/callbacks.h
        lib/callbacks/Display.cpp
        lib/callbacks/ReSize.cpp
        lib/callbacks/Setup.cpp
        lib/callbacks/keyboard.cpp
        lib/glTerrain/glTerrain.cpp
        lib/glTerrain/glTerrain.h
        lib/randRange/randRange.h
        lib/callbacks/Idle.cpp
        lib/callbacks/Close.cpp
        lib/callbacks/dbg.cpp
   )

##########################################################
# Project Setup ##########################################
##########################################################

cmake_minimum_required(VERSION 3.6)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

##########################################################
# OpenGL Setup ###########################################
##########################################################

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

##########################################################
# Output Setup ###########################################
##########################################################

set_target_properties( ${PROJECT_NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "../output/archive"
        LIBRARY_OUTPUT_DIRECTORY "../output/lib"
        RUNTIME_OUTPUT_DIRECTORY "../output/"
        )