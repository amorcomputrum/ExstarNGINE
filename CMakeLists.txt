cmake_minimum_required(VERSION 3.10)

# set the project name
#Verstion Official.Alpha.Beta
project(Exstar VERSION 0.0.1)
#Add Source Code
file(GLOB SOURCES src/*.cpp
		src/Physics/*.cpp
		src/Graphics/*.cpp
		src/Utils/*.cpp)
#include Headers
include_directories(include)

add_library(Exstar SHARED ${SOURCES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#Compile and Install glfw
add_subdirectory(Dependencies/glfw)
target_link_libraries(Exstar glfw)
target_compile_options(Exstar PUBLIC "-lglfw")
target_link_libraries(Exstar "-lglfw")
set_target_properties(Exstar PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(Exstar PROPERTIES SOVERSION 1)


#move included cpp files
install(FILES "src/Graphics/Camera.cpp" DESTINATION "include/Exstar/Graphics/")
install(FILES "src/Graphics/Sprite/Sprite.cpp" DESTINATION "include/Exstar/Graphics/Sprite/")
install(FILES "src/Utils/ArrayList.cpp" DESTINATION "include/Exstar/Utils/")
install(FILES "src/Physics/Shape.cpp" DESTINATION "include/Exstar/Physics/")
install(FILES "src/Physics/Body.cpp" DESTINATION "include/Exstar/Physics/")
install(FILES "src/Utils/Vector2d.cpp" DESTINATION "include/Exstar/Utils/")
install(FILES "src/Physics/World.cpp" DESTINATION "include/Exstar/Physics/")
#move Headers and SO
install(TARGETS Exstar DESTINATION lib/Exstar)
install(DIRECTORY "include/" # source directory
        DESTINATION "include" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.h" # select header files
)
