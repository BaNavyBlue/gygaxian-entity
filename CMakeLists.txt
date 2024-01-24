# TODO 1: Set the minimum required version of CMake to be 3.10
cmake_minimum_required(VERSION 3.12)
# TODO 2: Create a project named Tutorial
project(gygaxian-entity)

# TODO 7: Set the project version number as 1.0 in the above project command
project(gygaxian-entity VERSION 1.0)
# TODO 6: Set the variable CMAKE_CXX_STANDARD to 11
#         and the variable CMAKE_CXX_STANDARD_REQUIRED to True
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CXX_FLAGS "-g" "-Wall")
#set(WINDOWS_EXPORT_ALL_SYMBOLS YES CACHE BOOL "Export all symbols")

# TODO 8: Use configure_file to configure and copy TutorialConfig.h.in to
#         TutorialConfig.h

# TODO 3: Add an executable called Tutorial to the project
# Hint: Be sure to specify the source file as tutorial.cxx
include_directories(./include)

add_executable(ui-test ui-test.cpp "src/rogueutil.c" src/char_class.cpp src/dice_roll.cpp src/entity.cpp src/items.cpp src/simdjson.cpp src/skills.cpp src/StatHelpers.cpp src/ui_util.cpp)
# TODO 9: Use target_include_directories to include ${PROJECT_BINARY_DIR}
#
#add_library(WindowsHeaders IMPORTED INTERFACE)
#target_include_directories(WindowsHeaders INTERFACE $ENV{WindowsSdkDir}/Include/…)