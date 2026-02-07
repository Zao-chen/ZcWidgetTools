cmake_minimum_required(VERSION 3.16)

project(ZcWidgetTools VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

# ========== 构建库 ==========
add_library(ZcWidgetTools SHARED
    src/ZcWidgetTools_global.h
    src/zcstackedwidget.h
    src/zcstackedwidget.cpp
)

target_link_libraries(ZcWidgetTools PUBLIC
    Qt6::Core
    Qt6::Widgets
)

target_compile_definitions(ZcWidgetTools PRIVATE ZCWIDGETTOOLS_LIBRARY)

target_include_directories(ZcWidgetTools PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(ZcWidgetTools PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# ========== 构建示例程序 ==========
# 检查文件是否存在
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/example/mainwindow.cpp")
    message(STATUS "Found mainwindow.cpp")
else()
    message(FATAL_ERROR "mainwindow.cpp not found!")
endif()

add_executable(ZcWidgetTools-Example
    example/main.cpp
    example/mainwindow.h
    example/mainwindow.cpp
    example/mainwindow.ui
)

target_link_libraries(ZcWidgetTools-Example PRIVATE
    Qt6::Widgets
    ZcWidgetTools
)

# Windows: 自动复制 DLL
if(WIN32)
    add_custom_command(TARGET ZcWidgetTools-Example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:ZcWidgetTools>
        $<TARGET_FILE_DIR:ZcWidgetTools-Example>
        COMMENT "Copying ZcWidgetTools.dll"
    )
endif()
