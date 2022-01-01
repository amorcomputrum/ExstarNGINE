cmake_minimum_required(VERSION 3.09)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(EXSTAR VERSION 0.0.1)

include(GNUInstallDirs)

add_subdirectory(src)

install(TARGETS EXSTAR DESTINATION lib/)

install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/Exstar"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)