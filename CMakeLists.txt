cmake_minimum_required(VERSION 3.27)
project(RetroBasic)

set(CMAKE_CXX_STANDARD 17)

add_executable(RetroBasic main.cpp
        system/CharCell.h
        system/CharCell.h
        system/ScreenBuffer.cpp
        system/ScreenBuffer.h)

add_library(sfml_graphics SHARED IMPORTED)
set_target_properties(sfml_graphics PROPERTIES IMPORTED_LOCATION "/lib/x86_64-linux-gnu/libsfml-graphics.so")
add_library(sfml_window SHARED IMPORTED)
set_target_properties(sfml_window PROPERTIES IMPORTED_LOCATION "/lib/x86_64-linux-gnu/libsfml-window.so")
add_library(sfml_system SHARED IMPORTED)
set_target_properties(sfml_system PROPERTIES IMPORTED_LOCATION "/lib/x86_64-linux-gnu/libsfml-system.so")

TARGET_LINK_LIBRARIES(RetroBasic sfml_graphics sfml_window sfml_system)

add_custom_command(TARGET RetroBasic POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:RetroBasic>/assets)
