cmake_minimum_required(VERSION 3.15)

project(MyGeometryDashGIFMod)

# Füge Geode ein
include_directories("/path/to/Geode/include")

add_executable(MyGeometryDashGIFMod src/Main.cpp)

# Linke mit Geode und anderen notwendigen Bibliotheken
target_link_libraries(MyGeometryDashGIFMod Geode)
