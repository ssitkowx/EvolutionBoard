# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly

cmake_minimum_required (VERSION 3.5)
LIST                   (APPEND EXTRA_COMPONENT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/Hardware)
INCLUDE                ($ENV{IDF_PATH}/tools/cmake/project.cmake)
PROJECT                (EvolutionBoard)