#ifndef EXSTAR_BOX_H
#define EXSTAR_BOX_H

#include "Exstar/Physics/Shape.h"

namespace exstar{
	class Box : public exstar::Shape{
	public:
		Box(double w,double h);
	};
}
#endif