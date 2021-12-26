#include "Exstar/Physics/Circle.h"

exstar::Circle::Circle(double r){
	this->r = r;
	this->id = exstar::Shape::ID::Circle;
}