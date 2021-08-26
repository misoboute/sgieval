cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(sgieval)

option(BUILD_TESTING 
    "Whether unit tests should be built (requires Google Test framework)" true)

set(SGI_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(src)

if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()
