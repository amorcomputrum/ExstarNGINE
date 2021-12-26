#include "Exstar/Physics/Box.h"

exstar::Box::Box(double w,double h){
	this->w = w;
	this->h = h;
	this->id = exstar::Shape::ID::AABB;
	this->vertices = new exstar::ArrayList<exstar::Vector2d*>();
}
