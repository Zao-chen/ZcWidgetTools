cmake_minimum_required(VERSION 3.16)

project(ZcWidgetTools-Example VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(ZcWidgetTools-Example
    main.cpp
    mainwindow.h
    mainwindow.cpp
)

target_link_libraries(ZcWidgetTools-Example PRIVATE
    Qt6::Widgets
)

# 链接到 ZcWidgetTools 库
# 方式 1: 如果在同一个 CMake 项目中
# target_link_libraries(ZcWidgetTools-Example PRIVATE ZcWidgetTools)

# 方式 2: 手动指定路径（用于独立编译）
target_include_directories(ZcWidgetTools-Example PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../src
)

target_link_libraries(ZcWidgetTools-Example PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../build/ZcWidgetTools.lib  # Windows
    # ${CMAKE_CURRENT_SOURCE_DIR}/../../build/libZcWidgetTools.so  # Linux
)