cmake_minimum_required(VERSION 3.10)

# set the project name
project(Exstar VERSION 1.0.0)

find_package(glfw3 3.3 REQUIRED)


add_library(Exstar SHARED
	src/gl.c
	src/Utils/ArrayList.cpp
	src/Sprite/Image_Handler.cpp
	src/Utils/Exception.cpp
	src/Sprite/Sprite.cpp
	src/Utils/Color.cpp
	src/Utils/Math.cpp
	src/Utils/Vector2d.cpp
    src/Camera.cpp
    src/Clock.cpp
    src/Window.cpp
)
target_link_libraries(Exstar glfw)
set_target_properties(Exstar PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(Exstar PROPERTIES SOVERSION 1)
include_directories(include)

install(TARGETS Exstar DESTINATION lib/Exstar)
install(DIRECTORY "include/" # source directory
        DESTINATION "include" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.h" # select header files
)