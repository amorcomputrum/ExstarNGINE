#ifndef EngineCollision_H
#define EngineCollision_H
	#include "Exstar/Physics/PCollision.h"
	#include "Exstar/Utils/Vector2d.h"
	namespace exstar{
		class EngineCollision{
		public:
			static bool AABBvsAABB(exstar::PCollision* collision);
			static bool AABBvsCircle(exstar::PCollision* collision);
			static bool CirclevsCircle(exstar::PCollision* collision);
			static bool CirclevsPolygon(exstar::PCollision* collision);
			static bool PolygonvsPolygon(exstar::PCollision* collision);
			static float IntervalDistance(exstar::Vector2d a,exstar::Vector2d b);
		};
	}
	#include "Exstar/Physics/EngineCollision.cpp"
#endif