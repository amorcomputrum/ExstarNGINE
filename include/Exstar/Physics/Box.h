#pragma once
#include "Exstar/Physics/Shape.h"

namespace exstar{
	namespace physics{
		class Box : public exstar::physics::Shape{
		public:
			Box(double w,double h);
		};
	}
}