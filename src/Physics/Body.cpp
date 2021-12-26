#include "Exstar/Physics/Body.h"

exstar::Body::Body(exstar::Vector2d* position,float restitution,int mass,exstar::Shape* shape,std::string id){
	this->position =  position;
	this->velocity = new Vector2d(0.0,0.0);
	this->restitution = restitution;
	this->mass = mass;
	if(mass == 0){
		inv_mass = 0;
	}else{
		inv_mass = 1.0/mass;
	}
	switch(shape->id){
		case exstar::Shape::ID::Polygon:
			for(int i = 0; i < shape->vertices->size;i++){
				*shape->vertices->get(i) -= *position;
			}
			break;
		case exstar::Shape::ID::AABB:
			shape->vertices->replace(1,new Vector2d(0,0));
			shape->vertices->replace(2,new Vector2d(shape->w,0));
			shape->vertices->replace(3,new Vector2d(shape->w,shape->h));
			shape->vertices->replace(4,new Vector2d(0,shape->h));
			break;
	}
	this->shape = shape;
	this->id = id;

}
exstar::Body::Body(exstar::Vector2d* position,exstar::Vector2d* velocity,float restitution,int mass,exstar::Shape* shape,std::string id){
	this->position =  position;
	this->velocity = velocity;
	this->restitution = restitution;
	this->mass = mass;
	if(mass == 0){
		inv_mass = 0;
	}else{
		inv_mass = 1.0/mass;
	}
	switch(shape->id){
		case exstar::Shape::ID::Polygon:
			for(int i = 0; i < shape->vertices->size;i++){
				*shape->vertices->get(i) -= *position;
			}
			break;
		case exstar::Shape::ID::AABB:
			shape->vertices->replace(1,new Vector2d(0,0));
			shape->vertices->replace(2,new Vector2d(shape->w,0));
			shape->vertices->replace(3,new Vector2d(shape->w,shape->h));
			shape->vertices->replace(4,new Vector2d(0,shape->h));
			break;
	}
	this->shape = shape;
	this->id = id;
}
