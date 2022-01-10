#include "Exstar/Physics/ConvexPolygon.h"

exstar::physics::ConvexPolygon::ConvexPolygon(){
	vertices = new ArrayList<exstar::Vector2d*>();
	this->id = exstar::physics::Shape::ID::Polygon;
}
exstar::physics::ConvexPolygon::ConvexPolygon(exstar::Shape shape){
	vertices = new ArrayList<exstar::Vector2d*>();
	this->id = exstar::physics::Shape::ID::Polygon;
	for(int i = 0; i < shape.getSize(); i++){
		vertices->add(new exstar::Vector2d(shape.getVector(i).x,shape.getVector(i).y));
	}
}