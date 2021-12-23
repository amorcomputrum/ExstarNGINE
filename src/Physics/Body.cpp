#include "Exstar/Physics/Body.h"

exstar::Body::Body(exstar::Vector2d* position,float restitution,int mass,exstar::Shape* shape){
	this->position =  position;
	this->velocity = new Vector2d();
	this->restitution = restitution;
	this->mass = mass;
	if(mass == 0){
		inv_mass = 0;
	}else{
		inv_mass = 1/mass;
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
		inv_mass = 1/mass;
	}
	this->shape = shape;
}
