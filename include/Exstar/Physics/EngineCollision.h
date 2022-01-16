#pragma once
#include "Exstar/Physics/PCollision.h"
#include "Exstar/Utils/Vector2d.h"
namespace exstar{\
	namespace physics{
		class EngineCollision{
		public:
			static bool AABBvsAABB(exstar::physics::PCollision* collision);
			static bool AABBvsCircle(exstar::physics::PCollision* collision);
			static bool CirclevsCircle(exstar::physics::PCollision* collision);
			static bool CirclevsPolygon(exstar::physics::PCollision* collision);
			static bool PolygonvsPolygon(exstar::physics::PCollision* collision);
			static float IntervalDistance(exstar::Vector2d a,exstar::Vector2d b);
		};
	}
}
