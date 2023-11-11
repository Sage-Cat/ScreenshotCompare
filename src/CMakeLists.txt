find_package(Qt5 REQUIRED COMPONENTS Widgets Sql)


add_executable(ScreenshotCompare
    ${PROJECT_SOURCES}
)

target_link_libraries(ScreenshotCompare PRIVATE Qt5::Widgets Qt5::Sql Qt5::Core Qt5::Concurrent)

include(GNUInstallDirs)
