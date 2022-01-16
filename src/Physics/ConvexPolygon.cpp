#include "Exstar/Utils/Exception.h"
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
void exstar::physics::ConvexPolygon::add(unsigned int x,unsigned int y){
	vertices->add(new exstar::Vector2d(x,y));
}
void exstar::physics::ConvexPolygon::add(exstar::Vector2d vertex){
	if(vertex.x < 0 || vertex.y < 0){
		throw exstar::exception("exstar::physics::ConvexPolygon::add - Points cannot be negative");
	}
	add(vertex.x,vertex.y);
}
void exstar::physics::ConvexPolygon::add(exstar::Point vertex){
	if(vertex.x < 0 || vertex.y < 0){
		throw exstar::exception("exstar::physics::ConvexPolygon::add - Points cannot be negative");
	}
	add(vertex.x,vertex.y);
}
void  exstar::physics::ConvexPolygon::remove(unsigned int x,unsigned int y){
	int index = getIndex(x,y);
	if(index != -1){
		remove(index);
	}
}
void  exstar::physics::ConvexPolygon::remove(exstar::Vector2d vertex){
	remove(vertex.x,vertex.y);
}
void  exstar::physics::ConvexPolygon::remove(exstar::Point vertex){
	remove(vertex.x,vertex.y);
}
void  exstar::physics::ConvexPolygon::remove(int i){
	if(vertices->size == 3){
		throw exstar::exception("exstar::physics::ConvexPolygon::remove - Cannot have less than 3 verties");
	}
	vertices->remove(i);
}
int exstar::physics::ConvexPolygon::getSize(){
	return vertices->size;
}
exstar::Vector2d exstar::physics::ConvexPolygon::getVertex(int i){
	return *vertices->get(i);
}
int  exstar::physics::ConvexPolygon::getIndex(unsigned int x,unsigned int y){
	for(int i = 0; i < vertices->size; i++){
		exstar::Vector2d* vertex = vertices->get(i);
		if(vertex->x == x && vertex->y == y){
			return i;
		}
	}
	return -1;
}