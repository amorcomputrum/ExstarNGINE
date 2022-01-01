#ifndef EXSTAR_SHAPE_H
#define EXSTAR_SHAPE_H
#include "Exstar/Utils/ArrayList.h"
#include "Exstar/Utils/Vector2d.h"

namespace exstar{
	class Shape{
	public:
		enum ID{
			AABB,Circle,Polygon
		};
		ID id;
		ArrayList<exstar::Vector2d*>* vertices;
		float r;
		int w,h;
		void rotate(double radians);
	};
}
#endif