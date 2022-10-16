cmake_minimum_required(VERSION 3.9)

# This is important!
# When coding a library you must not use the
# CMAKE_PROJECT_NAME variable because it will
# assume the main project name instead of the
# library name, and this is bad!
# Your build will fail and you will get stuck.
set(LIBNAME sfmlplot)

project(
    ${LIBNAME} VERSION 0.1.0
    DESCRIPTION "Plot things in SFML environments"
    HOMEPAGE_URL https://github.com/ensismoebius/sfmlPlot
    LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCS src/Heatmap.cpp)
set(INCLUDE_DIRS include)
set(INCLUDE_FILES "${INCLUDE_DIRS}/Heatmap.h")

# Library
add_library(${LIBNAME} SHARED ${SRCS})

set_target_properties(${LIBNAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${LIBNAME} PROPERTIES SOVERSION ${PROJECT_VERSION})
set_target_properties(${LIBNAME} PROPERTIES PUBLIC_HEADER ${INCLUDE_FILES})

# Includes the headers
target_include_directories(${LIBNAME} PRIVATE ${INCLUDE_DIRS})

# For visualizations
find_package(SFML 2 REQUIRED COMPONENTS graphics system window)

# Libraries to link
set(SFML_LIBS sfml-system sfml-window sfml-graphics)
target_link_libraries(${LIBNAME} ${SFML_LIBS})

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/share/pkgconfig/${LIBNAME}.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/${LIBNAME}.pc
    @ONLY
)

install(TARGETS ${LIBNAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${LIBNAME}.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
)
