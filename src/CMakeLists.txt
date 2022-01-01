set(EXSTAR_SOURCE_FILES 
		Window.cpp
		Clock.cpp
		gl.c
		Graphics/Camera.cpp
		Graphics/Color.cpp
		Graphics/Sprite/Image_Handler.cpp
		Graphics/Sprite/Sprite.cpp
		Physics/Body.cpp
		Physics/Box.cpp
		Physics/Circle.cpp
		Physics/ConvexPolygon.cpp
		Physics/DetectCollision.cpp
		Physics/EngineCollision.cpp
		Physics/Shape.cpp
		Physics/TestCollider.cpp
		Utils/Exception.cpp
		Utils/Math.cpp
		Utils/Matrix2.cpp
		Utils/Point.cpp
		Utils/Vector2d.cpp
		Physics/Engine.cpp)
set(EXSTAR_HEADER_FILES
		../include/Exstar/Graphics/Sprite/stb_image.h
		../include/Exstar/Window.h
		../include/Exstar/Clock.h
		../include/Exstar/Key.h
		../include/Exstar/MouseEvent.h
		../include/Exstar/exstarglad/gl.h
		../include/Exstar/exstarKHR/khrplatform.h
		../include/Exstar/Graphics/Camera.h
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

add_library(EXSTAR SHARED ${EXSTAR_SOURCE_FILES} ${EXSTAR_HEADER_FILES})

target_include_directories(EXSTAR
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/../include
)

set_target_properties(EXSTAR PROPERTIES
	CXX_STANDARD_REQUIRED YES
	VERSION 0.0.1
	SOVERSION 0.0.1)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "src" FILES ${EXSTAR_SOURCE_FILES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/../include" PREFIX "include" FILES ${EXSTAR_HEADER_FILES})