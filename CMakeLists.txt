cmake_minimum_required(VERSION 3.9)
project(sfmlplot VERSION 0.1.0
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

set (SRCS
src/main.cpp
src/lib/Heatmap.cpp
)

# Executable
add_executable(${CMAKE_PROJECT_NAME} ${SRCS})

# Libraries to link
set(SFML_LIBS sfml-system sfml-window sfml-graphics)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBS})

target_link_libraries(${PROJECT_NAME} ${ARMADILLO_LIBRARIES})

