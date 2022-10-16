cmake_minimum_required(VERSION 3.9)
project(libsfmlplot VERSION 0.1.0
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
    add_library(${CMAKE_PROJECT_NAME} SHARED ${SRCS})

    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION})
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES PUBLIC_HEADER ${INCLUDE_FILES})

    # Includes the headers
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})

    # For visualizations
    find_package(SFML 2 REQUIRED COMPONENTS graphics system window)



    # Libraries to link
    set(SFML_LIBS sfml-system sfml-window sfml-graphics)
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBS})

    configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/share/pkgconfig/${PROJECT_NAME}.pc.in
	${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
	@ONLY
    )

    install(TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig
    )
