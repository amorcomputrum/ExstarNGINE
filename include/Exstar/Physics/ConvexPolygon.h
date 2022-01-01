#ifndef EXSTAR_CONVEXPOLYGON_H
#define EXSTAR_CONVEXPOLYGON_H
#include "Exstar/Physics/Shape.h"
#include "Exstar/Utils/Point.h"
namespace exstar{
	class ConvexPolygon : public exstar::Shape{
	public:
		ConvexPolygon();
		void add(double x,double y);
		void add(ArrayList<exstar::Point>* verts);
	};
}
#endif