#include "Exstar/Physics/ConvexPolygon.h"

exstar::physics::ConvexPolygon::ConvexPolygon(){
	vertices = new ArrayList<exstar::Vector2d*>();
	this->id = exstar::physics::Shape::ID::Polygon;
}
void exstar::physics::ConvexPolygon::add(double x,double y){
	vertices->add(new exstar::Vector2d(x,y));
}
void exstar::physics::ConvexPolygon::add(ArrayList<exstar::Point>* verts){
	for(int i = 0; i < verts->size;i++){
		add(verts->get(i).x,verts->get(i).y);
	}
}