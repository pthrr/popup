cmake_minimum_required(VERSION 3.27 FATAL_ERROR)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectVersion.cmake)

project(
  popup
  LANGUAGES C CXX
  VERSION ${PROJECT_VERSION}
  DESCRIPTION "Popup")

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ProjectSettings.cmake)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(spdlog REQUIRED)
find_package(CLI11 REQUIRED)

add_subdirectory(src)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/build/compile_commands.json
)
