#ifndef EXSTAR_CIRCLE_H
#define EXSTAR_CIRCLE_H
	#include "Exstar/Physics/Shape.h"

	namespace exstar{
		class Circle : public exstar::Shape{
		public:
			Circle(double r);
		};
	}
	#include "Exstar/Physics/Circle.cpp"
#endif