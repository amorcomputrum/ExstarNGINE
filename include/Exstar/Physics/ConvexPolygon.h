#ifndef EXSTAR_CONVEXPOLYGON_H
#define EXSTAR_CONVEXPOLYGON_H
#include "Exstar/Physics/Shape.h"
#include "Exstar/Graphics/Shape.h"
#include "Exstar/Utils/Point.h"
namespace exstar{
	namespace physics{
		class ConvexPolygon : public exstar::physics::Shape{
		public:
			ConvexPolygon();
			ConvexPolygon(exstar::Shape shape);
		};
	}
}
#endif