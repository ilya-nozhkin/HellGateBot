project(Console)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++17 -Wno-deprecated-declarations")
add_executable(${PROJECT_NAME} ${SRC_LIST})

find_package(PkgConfig)
pkg_check_modules(LIBXML QUIET libxml-2.0)
pkg_check_modules(LIBCURL QUIET libcurl)
pkg_check_modules(LIBXMLPP QUIET libxml++-2.6)

find_package(Qt5 COMPONENTS Core WebEngine)

include_directories(${Qt5WebEngine_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${LIBXML_INCLUDE_DIRS} ${LIBCURL_INCLUDE_DIRS} ${LIBXMLPP_INCLUDE_DIRS})

set(LOCAL_LIB "${CMAKE_CURRENT_LIST_DIR}/../bin")
find_library(CORE_LIB Core HINTS ${LOCAL_LIB})
target_link_libraries(${PROJECT_NAME} ${CORE_LIB} curlpp curl xml++-2.6 xml2 glibmm-2.4 Qt5Core Qt5Gui Qt5Widgets Qt5WebEngine Qt5WebEngineCore Qt5WebEngineWidgets )
