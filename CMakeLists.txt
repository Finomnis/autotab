#Require a minimum version of CMake
cmake_minimum_required(VERSION 2.8.4 FATAL_ERROR)

#This project is C++ based.
project(autotab CXX)

# add our cmake path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/" ${CMAKE_MODULE_PATH} )


set(SOURCES
    main.cpp
    autotab.cpp
    table.cpp
    cmdline.cpp
)

set(HEADERS
    table.hpp
    autotab.hpp
    cmdline.hpp
)

add_executable(autotab ${SOURCES} ${HEADERS})

install(TARGETS autotab DESTINATION bin)
