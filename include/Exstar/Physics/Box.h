#ifndef EXSTAR_BOX_H
#define EXSTAR_BOX_H

#include "Exstar/Physics/Shape.h"

namespace exstar{
	namespace physics{
		class Box : public exstar::physics::Shape{
		public:
			Box(double w,double h);
		};
	}
}
#endif