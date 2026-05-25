cmake_minimum_required(VERSION 3.16)

project(ZcWidgetTools VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

if(APPLE)
    foreach(qt_target Qt6::Widgets Qt6::Gui Qt6::Core)
        if(TARGET ${qt_target})
            foreach(qt_prop INTERFACE_LINK_LIBRARIES INTERFACE_LINK_OPTIONS)
                get_target_property(qt_values ${qt_target} ${qt_prop})
                if(qt_values)
                    list(FILTER qt_values EXCLUDE REGEX "AGL")
                    set_property(TARGET ${qt_target} PROPERTY ${qt_prop} "${qt_values}")
                endif()
            endforeach()
        endif()
    endforeach()

    foreach(gl_target OpenGL::OpenGL OpenGL::GL OpenGL::GLU)
        if(TARGET ${gl_target})
            foreach(gl_prop INTERFACE_LINK_LIBRARIES INTERFACE_LINK_OPTIONS)
                get_target_property(gl_values ${gl_target} ${gl_prop})
                if(gl_values)
                    list(FILTER gl_values EXCLUDE REGEX "AGL")
                    set_property(TARGET ${gl_target} PROPERTY ${gl_prop} "${gl_values}")
                endif()
            endforeach()
        endif()
    endforeach()

    if(TARGET WrapOpenGL::WrapOpenGL)
        foreach(wrap_prop INTERFACE_LINK_LIBRARIES INTERFACE_LINK_OPTIONS)
            get_target_property(wrap_values WrapOpenGL::WrapOpenGL ${wrap_prop})
            if(wrap_values)
                list(FILTER wrap_values EXCLUDE REGEX "AGL")
                set_property(TARGET WrapOpenGL::WrapOpenGL PROPERTY ${wrap_prop} "${wrap_values}")
            endif()
        endforeach()
    endif()
endif()

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
