cmake_minimum_required(VERSION 3.10)

# set the project name
project(Exstar VERSION 1.0.0)

add_library(Exstar SHARED
	src/gl.c
	src/Utils/ArrayList.cpp
	src/Sprite/Image_Handler.cpp
	src/Utils/Exception.cpp
	src/Utils/Color.cpp
	src/Utils/Math.cpp
	src/Utils/Vector2d.cpp
	src/Clock.cpp
	src/Window.cpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(Dependencies)
target_link_libraries(Exstar glfw)
target_compile_options(Exstar PUBLIC "-lglfw")
target_link_libraries(Exstar "-lglfw")
set_target_properties(Exstar PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(Exstar PROPERTIES SOVERSION 1)
include_directories(include)


install(FILES "src/Camera.cpp" DESTINATION "include/Exstar/")
install(FILES "src/Sprite/Sprite.cpp" DESTINATION "include/Exstar/Sprite/")
install(TARGETS Exstar DESTINATION lib/Exstar)
install(DIRECTORY "include/" # source directory
        DESTINATION "include" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.h" # select header files
)
