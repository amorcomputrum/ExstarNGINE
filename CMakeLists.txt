cmake_minimum_required(VERSION 3.10)

# set the project name
project(Exstar VERSION 1.0.0)
#Add Source Code
add_library(Exstar SHARED
	src/gl.c
	src/Graphics/Sprite/Image_Handler.cpp
	src/Utils/Exception.cpp
	src/Graphics/Color.cpp
	src/Utils/Math.cpp
	src/Utils/Vector2d.cpp
	src/Clock.cpp
	src/Window.cpp
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#Compile and Install glfw
add_subdirectory(Dependencies)
target_link_libraries(Exstar glfw)
target_compile_options(Exstar PUBLIC "-lglfw")
target_link_libraries(Exstar "-lglfw")
set_target_properties(Exstar PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(Exstar PROPERTIES SOVERSION 1)
#include Headers
include_directories(include)

#move included cpp files
install(FILES "src/Graphics/Camera.cpp" DESTINATION "include/Exstar/Graphics/")
install(FILES "src/Graphics/Sprite/Sprite.cpp" DESTINATION "include/Exstar/Graphics/Sprite/")
install(FILES "src/Utils/ArrayList.cpp" DESTINATION "include/Exstar/Utils/")
#move Headers and SO
install(TARGETS Exstar DESTINATION lib/Exstar)
install(DIRECTORY "include/" # source directory
        DESTINATION "include" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.h" # select header files
)
