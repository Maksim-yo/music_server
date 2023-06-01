cmake_minimum_required(VERSION 3.14)

project(music_server)
set(ROOT "D:/code/c++/proj/music_app/music_server")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "D:/odb/odb-2.4.0-i686-windows/odb-2.4.0-i686-windows")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "D:/odb/libodb-qt-2.4.0/libodb-qt-2.4.0")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "D:/odb/libodb-pgsql-2.4.0/libodb-pgsql-2.4.0")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "D:/code/c++/googletest-1.13.0/")


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Gui)




add_subdirectory(src)


