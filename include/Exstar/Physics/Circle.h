#ifndef EXSTAR_CIRCLE_H
#define EXSTAR_CIRCLE_H
#include "Exstar/Physics/Shape.h"

namespace exstar{
	namespace physics{
		class Circle : public exstar::physics::Shape{
		public:
			Circle(double r);
		};
	}
}
#endif