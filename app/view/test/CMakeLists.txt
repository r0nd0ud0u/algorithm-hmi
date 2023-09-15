cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

project(tests)

set(SOURCES
)

add_executable(${PROJECT_NAME} ${SOURCES})

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(${PROJECT_NAME} PUBLIC 
        Qt5::Core
        calculations
        gtestd
        gtest_maind
    )
else()
    if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(${PROJECT_NAME} PUBLIC 
        Qt5::Core
        calculations
        gtest
        gtest_main
    )
    endif()
endif()


