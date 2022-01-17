#include "Exstar/Physics/Circle.h"

exstar::physics::Circle::Circle(double r){
	this->r  = r;
	this->id = exstar::physics::Shape::ID::Circle;
}