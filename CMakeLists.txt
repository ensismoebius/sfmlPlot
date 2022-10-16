cmake_minimum_required(VERSION 3.9)
project(sfmlplotTesting VERSION 0.1.0
        DESCRIPTION "Plot things in SFML environments"
        LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# For visualizations
find_package(SFML 2 REQUIRED COMPONENTS graphics system window)

# Compiles the dependecies too
add_subdirectory("lib")
include_directories("lib/include")

set (SRCS
src/main.cpp
)

# Executable
add_executable(${CMAKE_PROJECT_NAME} ${SRCS})

# Copies the used font to folder
file(
    COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/fonts/Arial.ttf
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/fonts
)

# Libraries to link
set(SFML_LIBS sfml-system sfml-window sfml-graphics)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBS})






