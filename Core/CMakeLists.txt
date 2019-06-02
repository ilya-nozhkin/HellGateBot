project(Core)
cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++17 -Wno-deprecated-declarations")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../bin)

find_package(PkgConfig)
pkg_check_modules(LIBXML QUIET libxml-2.0)
pkg_check_modules(LIBCURL QUIET libcurl)
pkg_check_modules(LIBXMLPP QUIET libxml++-2.6)

find_package(Qt5 COMPONENTS Core WebEngine WebEngineWidgets)

include_directories(${Qt5WebEngine_INCLUDE_DIRS} ${Qt5WebEngineWidgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${LIBXML_INCLUDE_DIRS} ${LIBCURL_INCLUDE_DIRS} ${LIBXMLPP_INCLUDE_DIRS})

file(GLOB SRC_LIST . *.cpp)
file(GLOB HEADERS_LIST . *.h)
add_library(${PROJECT_NAME} ${SRC_LIST} ${HEADERS_LIST})
target_link_libraries(${PROJECT_NAME} curl)
