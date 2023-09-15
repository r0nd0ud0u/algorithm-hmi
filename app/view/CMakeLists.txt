project(view)

# Qt pre-compilation activation
set(CMAKE_AUTOUIC_SEARCH_PATHS ./forms)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
        src/mainwindow.cpp
        src/gridgame.cpp
        src/pathfinderpanel.cpp
)

set(HEADERS
        include/mainwindow.h
        include/gridgame.h
        include/pathfinderpanel.h
)

set(FORMS
        forms/mainwindow.ui
        forms/gridgame.ui
        forms/pathfinderpanel.ui
)

add_library(view STATIC ${SOURCES} ${HEADERS} ${FORMS})

target_include_directories(view PUBLIC include forms)

target_link_libraries(view
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)
