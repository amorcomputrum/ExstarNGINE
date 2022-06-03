cmake_minimum_required(VERSION 3.09)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(EXSTAR VERSION 0.2.3)

include(GNUInstallDirs)

option(BUILD_STATIC "Build Static Libraries" OFF)

#Compile and Install glfw
find_library(GLFW3_FOUND glfw3)
if(NOT BUILD_STATIC)
    if(NOT GLFW3_FOUND)
        add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw")
    endif(GLFW3_FOUND)
endif()

if(BUILD_STATIC)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "disable shared libs" FORCE)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw")
endif()

add_subdirectory(src)

install(TARGETS Exstar DESTINATION lib/)

install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/Exstar"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)