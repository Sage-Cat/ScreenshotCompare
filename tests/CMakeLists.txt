find_package(Qt5Test REQUIRED)

set(TEST_SOURCES_DIR "${TEST_SOURCES_DIR}") 
file(GLOB TEST_SOURCES "${TEST_SOURCES_DIR}/*.cpp")

foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_include_directories(${TEST_NAME} PUBLIC ${PROJECT_SOURCES_DIR})
    target_link_libraries(${TEST_NAME} Qt5::Test)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

    # Define the test binary directory
    target_compile_definitions(${TEST_NAME} PRIVATE -DTEST_BINARY_DIR="${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endforeach()
