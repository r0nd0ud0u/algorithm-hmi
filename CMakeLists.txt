cmake_minimum_required(VERSION 3.5)

project(algorithm-hmi VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Network)

include(${CMAKE_SOURCE_DIR}/build_conan/${CMAKE_BUILD_TYPE}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(app)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(algorithm-hmi
        MANUAL_FINALIZATION
        app/view/src/main.cpp
    )
else()
    if(ANDROID)
        add_library(algorithm-hmi SHARED
            app/view/src/main.cpp
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(algorithm-hmi
            app/view/src/main.cpp
        )
    endif()
endif()

target_link_libraries(algorithm-hmi PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Network
    view
)

set_target_properties(algorithm-hmi PROPERTIES
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(algorithm-hmi)
endif()
