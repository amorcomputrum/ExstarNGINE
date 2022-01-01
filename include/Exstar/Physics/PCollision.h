#ifndef EXSTAR_PCOLLISION_H
#define EXSTAR_PCOLLISION_H
#include "Exstar/Physics/Body.h"
namespace exstar{
	struct PCollision{
		exstar::Body* A;
		exstar::Body* B;
		float penetration = 0;
		exstar::Vector2d normal = exstar::Vector2d();
	};
}
#endif