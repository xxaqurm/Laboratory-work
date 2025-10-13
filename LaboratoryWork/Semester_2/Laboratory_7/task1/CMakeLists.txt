cmake_minimum_required(VERSION 3.5)
project(task1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt6_add_executable(task1 main.cpp)

target_link_libraries(task1 PRIVATE Qt6::Widgets)
