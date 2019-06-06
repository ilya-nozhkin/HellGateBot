project(CoreTests)
cmake_minimum_required(VERSION 2.8.11)
aux_source_directory(. SRC_LIST)

IF (WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_HAS_AUTO_PTR_ETC=1 /std:c++17")
	
        macro(QT_PACKAGE pkg)
		set(CMAKE_PREFIX_PATH ${QT_MODULES_DIR}/${pkg})
		find_package(${pkg})
	endmacro(QT_PACKAGE)

	QT_PACKAGE(Qt5Core)
	QT_PACKAGE(Qt5Gui)
	QT_PACKAGE(Qt5Widgets)
	QT_PACKAGE(Qt5WebEngine)
	QT_PACKAGE(Qt5WebEngineCore)
	QT_PACKAGE(Qt5WebEngineWidgets)
	
	set(LIBXML_LIBRARIES libxml2)
	set(LIBXMLPP_LIBRARIES xml++)
	set(ADDITIONAL_LIBRARIES legacy_stdio_definitions iconv Ws2_32 gtest microhttpd pthread httpmockserver)
	set(CORE_LIB "${CMAKE_CURRENT_LIST_DIR}/../build/bin/Release/Core.lib")
ELSE()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++17 -Wno-deprecated-declarations")
	
	find_package(Qt5 COMPONENTS Core Gui Widgets WebEngine WebEngineCore WebEngineWidgets)
	
	find_package(PkgConfig)
	pkg_check_modules(LIBXML QUIET libxml-2.0)
	pkg_check_modules(LIBXMLPP QUIET libxml++-2.6)
    set(CORE_LIB "${CMAKE_CURRENT_BINARY_DIR}/../Core/libCore.a")
    set(MOCK_SERVER "${CMAKE_CURRENT_BINARY_DIR}/../httpmockserver/src/libhttpmockserver.a")
    set(ADDITIONAL_LIBRARIES gtest microhttpd pthread ${MOCK_SERVER})

    include_directories(${CMAKE_CURRENT_LIST_DIR}/../httpmockserver/include)
ENDIF()

add_executable(${PROJECT_NAME} ${SRC_LIST})

add_definitions(-DMOCK_PAGES_PATH="${CMAKE_CURRENT_LIST_DIR}/MockPages")

include_directories(${Qt5WebEngine_INCLUDE_DIRS} ${Qt5WebEngineWidgets_INCLUDE_DIRS} ${Qt5WebEngineCore_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})
include_directories(${LIBXML_INCLUDE_DIRS} ${LIBXMLPP_INCLUDE_DIRS})

set(QT_LIBS ${Qt5Core_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES}
    ${Qt5WebEngine_LIBRARIES} ${Qt5WebEngineCore_LIBRARIES} ${Qt5WebEngineWidgets_LIBRARIES})

target_link_libraries(${PROJECT_NAME} ${CORE_LIB} ${QT_LIBS} ${LIBXML_LIBRARIES} ${LIBXMLPP_LIBRARIES} ${ADDITIONAL_LIBRARIES})
