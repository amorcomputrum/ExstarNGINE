#include "Exstar/Physics/Shape.h"

exstar::Shape::Shape(){}

exstar::Shape::Shape(float r){
	id = exstar::Shape::ID::Circle;
	this->r = r;
}
exstar::Shape::Shape(exstar::ArrayList<exstar::Point>* vertices,exstar::ArrayList<exstar::Point>* normals){
	id = exstar::Shape::ID::Polygon;
	this->vertices = vertices;
	this->normals = normals;
}
