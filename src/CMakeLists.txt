if(POLICY CMP0084)
  cmake_policy(SET CMP0084 NEW)
endif()

find_package(Qt5 REQUIRED COMPONENTS Widgets Sql)

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

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ScreenshotCompare
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(ScreenshotCompare SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ScreenshotCompare
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ScreenshotCompare PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ScreenshotCompare)
endif()

set_target_properties(ScreenshotCompare PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ScreenshotCompare
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ScreenshotCompare)
endif()
