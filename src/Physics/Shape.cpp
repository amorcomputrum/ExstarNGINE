#include <float.h>

#include "Exstar/Physics/Shape.h"
#include "Exstar/Utils/Math.h"

void exstar::physics::Shape::rotate(double rotate){
	for(int i = 0;i < vertices->size;i++){
		vertices->get(i)->x = vertices->get(i)->x*cos(rotate*3.14/180) - vertices->get(i)->y*sin(rotate*3.14/180);
		vertices->get(i)->y = vertices->get(i)->y*cos(rotate*3.14/180) + vertices->get(i)->x*sin(rotate*3.14/180);
	}
}
