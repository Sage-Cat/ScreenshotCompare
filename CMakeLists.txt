cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ScreenshotCompare VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Concurrent Widgets Sql Test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()
option(BUILD_TESTING "Build the testing tree." ON)

set(PROJECT_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(PROJECT_SOURCES
        ${PROJECT_SOURCES_DIR}/main.cpp
        ${PROJECT_SOURCES_DIR}/mainwindow.cpp
        ${PROJECT_SOURCES_DIR}/mainwindow.hpp
        ${PROJECT_SOURCES_DIR}/screenshot_service.cpp
        ${PROJECT_SOURCES_DIR}/screenshot_service.hpp
        ${PROJECT_SOURCES_DIR}/image_comparison_module.cpp 
        ${PROJECT_SOURCES_DIR}/image_comparison_module.hpp 
        ${PROJECT_SOURCES_DIR}/database_module.cpp 
        ${PROJECT_SOURCES_DIR}/database_module.hpp 
)

set(TEST_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")

# SUBDIRS
add_subdirectory(src)
add_subdirectory(tests)