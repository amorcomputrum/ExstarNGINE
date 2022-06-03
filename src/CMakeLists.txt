set(EXSTAR_SOURCE_FILES 
		Window.cpp
		Clock.cpp
		gl.c
		Generation/Line.cpp
		Generation/PerlinNoise.cpp
		Graphics/Graphics.cpp
		Graphics/Shape.cpp
		Graphics/Shaders/GLSL.cpp
		Graphics/Color.cpp
		Graphics/Sprite/Image_Handler.cpp
		Graphics/Sprite/Sprite.cpp
		Physics/Body.cpp
		Physics/Box.cpp
		Physics/Circle.cpp
		Physics/ConvexPolygon.cpp
		Physics/DetectCollision.cpp
		Physics/Engine.cpp
		Physics/EngineCollision.cpp
		Physics/TestCollider.cpp
		System/File.cpp
		Utils/Exception.cpp
		Utils/Math.cpp
		Utils/Matrix2.cpp
		Utils/Vector2d.cpp)

if (BUILD_STATIC)
	add_library(Exstar STATIC ${EXSTAR_SOURCE_FILES})
else()
	add_library(Exstar SHARED ${EXSTAR_SOURCE_FILES})
endif()


target_include_directories(Exstar
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(Exstar glfw)
target_compile_options(Exstar PUBLIC "-lglfw")
target_link_libraries(Exstar "-lglfw")

set_target_properties(Exstar PROPERTIES
	CXX_STANDARD_REQUIRED YES
	VERSION ${CMAKE_PROJECT_VERSION}
	SOVERSION ${CMAKE_PROJECT_VERSION})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "src" FILES ${EXSTAR_SOURCE_FILES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
