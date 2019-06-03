project(CoreTests)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++17 -Wno-deprecated-declarations")
add_executable(${PROJECT_NAME} ${SRC_LIST})

add_definitions(-DMOCK_PAGES_PATH="${CMAKE_CURRENT_LIST_DIR}/MockPages")

find_package(PkgConfig)
pkg_check_modules(LIBXML QUIET libxml-2.0)
pkg_check_modules(LIBXMLPP QUIET libxml++-2.6)

find_package(Qt5 COMPONENTS Core Gui Widgets WebEngine WebEngineCore WebEngineWidgets)

include_directories(${Qt5WebEngine_INCLUDE_DIRS} ${Qt5WebEngineWidgets_INCLUDE_DIRS} ${Qt5WebEngineCore_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})
include_directories(${LIBXML_INCLUDE_DIRS} ${LIBXMLPP_INCLUDE_DIRS})
include_directories("${CMAKE_CURRENT_LIST_DIR}/../build/include")

set(QT_LIBS ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES}
    ${Qt5WebEngine_LIBRARIES} ${Qt5WebEngineCore_LIBRARIES} ${Qt5WebEngineWidgets_LIBRARIES})

set(LOCAL_LIB "${CMAKE_CURRENT_LIST_DIR}/../build/bin")
find_library(CORE_LIB Core HINTS ${LOCAL_LIB})
find_library(HTTP_MOCK_SERVER_LIB httpmockserver HINTS ${LOCAL_LIB})
target_link_libraries(${PROJECT_NAME} ${CORE_LIB} ${QT_LIBS} ${LIBXML_LIBRARIES} ${LIBXMLPP_LIBRARIES} ${HTTP_MOCK_SERVER_LIB} gtest microhttpd pthread)
