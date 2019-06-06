project(Core)
cmake_minimum_required(VERSION 2.8)

IF (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_HAS_AUTO_PTR_ETC=1 /std:c++17")
	
	macro(QT_PACKAGE pkg)
		set(CMAKE_PREFIX_PATH ${QT_MODULES_DIR}/${pkg})
		find_package(${pkg})
	endmacro(QT_PACKAGE)

	QT_PACKAGE(Qt5Core)
	QT_PACKAGE(Qt5WebEngine)
	QT_PACKAGE(Qt5WebEngineWidgets)
ELSE()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++17 -Wno-deprecated-declarations")
	
	find_package(Qt5 COMPONENTS Core Gui Widgets WebEngine WebEngineCore WebEngineWidgets)
	
	find_package(PkgConfig)
	pkg_check_modules(LIBXML QUIET libxml-2.0)
	pkg_check_modules(LIBXMLPP QUIET libxml++-2.6)
	include_directories(${LIBXML_INCLUDE_DIRS} ${LIBXMLPP_INCLUDE_DIRS})
ENDIF()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../build/bin)

include_directories(${Qt5WebEngine_INCLUDE_DIRS} ${Qt5WebEngineWidgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS})

file(GLOB SRC_LIST . *.cpp)
file(GLOB HEADERS_LIST . *.h)
add_library(${PROJECT_NAME} ${SRC_LIST} ${HEADERS_LIST})
target_link_libraries(${PROJECT_NAME} curl)
