#include "Exstar/Physics/Body.h"
namespace exstar{
	struct PCollision{
		exstar::Body* A;
		exstar::Body* B;
		float penetration;
		exstar::Vector2d normal;
	};
}