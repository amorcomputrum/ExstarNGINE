#include "Exstar/Physics/Body.h"

exstar::Body::Body(exstar::Vector2d* position,float restitution,int mass,exstar::Shape* shape){
	this->position =  position;
	this->velocity = new Vector2d(0.0,0.0);
	this->restitution = restitution;
	this->mass = mass;
	if(mass == 0){
		inv_mass = 0;
	}else{
		inv_mass = 1.0/mass;
	}
	if(shape->id == exstar::Shape::ID::Polygon){
		for(int i = 0; i < shape->vertices->size;i++){
			*shape->vertices->get(i) -= *position;
			*shape->vertices->get(i) *= exstar::Vector2d(1,-1);
		}
	}
	this->shape = shape;

}
exstar::Body::Body(exstar::Vector2d* position,exstar::Vector2d* velocity,float restitution,int mass,exstar::Shape* shape){
	this->position =  position;
	this->velocity = velocity;
	this->restitution = restitution;
	this->mass = mass;
	if(mass == 0){
		inv_mass = 0;
	}else{
		inv_mass = 1.0/mass;
	}
	if(shape->id == exstar::Shape::ID::Polygon){
		for(int i = 0; i < shape->vertices->size;i++){
			*shape->vertices->get(i) -= *position;
			*shape->vertices->get(i) *= exstar::Vector2d(1,-1);
		}
	}
	this->shape = shape;
}
