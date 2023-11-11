cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ScreenshotCompare VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()
option(BUILD_TESTING "Build the testing tree." ON)

set(PROJECT_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(TEST_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")

# SUBDIRS
add_subdirectory(src)
add_subdirectory(tests)