#ifndef EXSTAR_PCOLLISION_H
#define EXSTAR_PCOLLISION_H
#include "Exstar/Physics/Body.h"
namespace exstar{
	namespace physics{
		struct PCollision{
			exstar::physics::Body* A;
			exstar::physics::Body* B;
			float penetration = 0;
			exstar::Vector2d normal = exstar::Vector2d();
		};
	}
}
#endif