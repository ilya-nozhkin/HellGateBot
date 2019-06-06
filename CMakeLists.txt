project(HellGateBot)
cmake_minimum_required(VERSION 2.8.11)

add_subdirectory(Core)
add_subdirectory(CoreTests)
add_subdirectory(Console)

add_dependencies(CoreTests Core)
add_dependencies(Console Core)