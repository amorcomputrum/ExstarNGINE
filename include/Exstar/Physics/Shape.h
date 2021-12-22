#ifndef Shape_H
#define Shape_H
	#include "Exstar/Utils/ArrayList.h"
	#include "Exstar/Utils/Point.h"
	namespace exstar{
		class Shape{
		public:
			enum ID{
				Circle,
				Polygon
			};
			ID id;
			float r;
			exstar::ArrayList<exstar::Point>* vertices;
			exstar::ArrayList<exstar::Point>* normals;
			Shape();
			Shape(float r);
			Shape(exstar::ArrayList<exstar::Point>* vertices,exstar::ArrayList<exstar::Point>* normals);
		};
	}
	#include "Exstar/Physics/Shape.cpp"
#endif