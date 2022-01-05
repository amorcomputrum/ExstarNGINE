set(EXSTAR_SOURCE_FILES 
		Window.cpp
		Clock.cpp
		gl.c
		Generation/Line.cpp
		Generation/PerlinNoise.cpp
		Graphics/Graphics.cpp
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
		Physics/Shape.cpp
		Physics/TestCollider.cpp
		Utils/Exception.cpp
		Utils/Math.cpp
		Utils/Matrix2.cpp
		Utils/Vector2d.cpp)
set(EXSTAR_HEADER_FILES
		../include/Exstar/Graphics/Sprite/stb_image.h
		../include/Exstar/Window.h
		../include/Exstar/Clock.h
		../include/Exstar/Key.h
		../include/Exstar/MouseEvent.h
		../include/Exstar/exstarglad/gl.h
		../include/Exstar/exstarKHR/khrplatform.h
		../include/Exstar/Generation/Line.h
		../include/Exstar/Generation/PerlinNoise.h
		../include/Exstar/Graphics/Graphics.h
		../include/Exstar/Graphics/Color.h
		../include/Exstar/Graphics/Sprite/Image_Handler.h
		../include/Exstar/Graphics/Sprite/Sprite.h
		../include/Exstar/Physics/Body.h
		../include/Exstar/Physics/Box.h
		../include/Exstar/Physics/Circle.h
		../include/Exstar/Physics/ConvexPolygon.h
		../include/Exstar/Physics/DetectCollision.h
		../include/Exstar/Physics/EngineCollision.h
		../include/Exstar/Physics/PCollision.h
		../include/Exstar/Physics/Shape.h
		../include/Exstar/Physics/TestCollider.h
		../include/Exstar/Utils/ArrayList.h
		../include/Exstar/Utils/Dimension.h
		../include/Exstar/Utils/Exception.h
		../include/Exstar/Utils/Math.h
		../include/Exstar/Utils/Matrix2.h
		../include/Exstar/Utils/Point.h
		../include/Exstar/Utils/Vector2d.h
		../include/Exstar/Physics/Engine.h)

add_library(Exstar SHARED ${EXSTAR_SOURCE_FILES} ${EXSTAR_HEADER_FILES})

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
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/../include" PREFIX "include" FILES ${EXSTAR_HEADER_FILES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
