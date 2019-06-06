project(HellGateBot)
cmake_minimum_required(VERSION 2.8.11)

IF (WIN32)
ELSE()
    set(USE_SYSTEM_CURL YES)
    set(USE_SYSTEM_GTEST ON)
    set(USE_SYSTEM_OPENSSL OFF)
    set(CMAKE_DEBUG_POSTFIX "")
    set(CMAKE_DEBUG_POSTFIX "")
    add_subdirectory(httpmockserver)
ENDIF()

add_subdirectory(Core)
add_subdirectory(CoreTests)
add_subdirectory(Console)

IF (WIN32)
    add_dependencies(CoreTests Core)
ELSE()
    add_dependencies(CoreTests Core httpmockserver)
ENDIF()

add_dependencies(Console Core)
