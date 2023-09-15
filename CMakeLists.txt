cmake_minimum_required(VERSION 3.5)

project(gred VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
CentralWidget.cpp
CentralWidget.h
Circle.cpp
Circle.h
Command.cpp
Command.h
CopyInsertCommand.cpp
CopyInsertCommand.h
CreateCommand.cpp
CreateCommand.h
DeleteCommand.cpp
DeleteCommand.h
DrawerLabel.cpp
DrawerLabel.h
Ellipse.cpp
Ellipse.h
Figure.cpp
Figure.h
Line.cpp
Line.h
main.cpp
MainWnd.cpp
MainWnd.h
MoveAngleCommand.cpp
MoveAngleCommand.h
MoveCommand.cpp
MoveCommand.h
Picture.cpp
Picture.h
Point.cpp
Point.h
PrimitiveFigure.cpp
PrimitiveFigure.h
Square.cpp
Square.h
TouchCommand.cpp
TouchCommand.h
Triangle.cpp
Triangle.h
MainWnd.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(gred
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET test_qt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(gred SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(gred
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(gred PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(gred PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS gred
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(gred)
endif()

if(MSVC)
  target_compile_options(<target> PUBLIC "/ZI")
  target_link_options(<target> PUBLIC "/INCREMENTAL")
endif()
