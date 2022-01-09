#include <float.h>
#include <math.h>

#include "Exstar/Physics/Body.h"

exstar::Body::Body(exstar::Vector2d position,float restitution,int mass,exstar::Shape* shape,std::string id){
	this->position =  new exstar::Vector2d(position.x,position.y);
	this->velocity = new exstar::Vector2d(0.0,0.0);
	this->restitution = restitution;
	this->mass = mass;
	this->id = id;
	if(mass == 0){
		inv_mass = 0.0;
	}else{
		inv_mass = 1.0/mass;
	}
	switch(shape->id){
		case exstar::Shape::ID::AABB:
			shape->vertices->add(new Vector2d(0,0));
			shape->vertices->add(new Vector2d(shape->w,0));
			shape->vertices->add(new Vector2d(shape->w,shape->h));
			shape->vertices->add(new Vector2d(0,shape->h));
			break;
	}
	this->shape = shape;
	force = new exstar::Vector2d();
	updateCollider();
}
exstar::Body::Body(exstar::Vector2d position,exstar::Vector2d velocity,float restitution,int mass,exstar::Shape* shape,std::string id){
	this->position =  new exstar::Vector2d(position.x,position.y);
	this->velocity = new exstar::Vector2d(velocity.x,velocity.y);
	this->restitution = restitution;
	this->mass = mass;
	this->id = id;
	if(mass == 0){
		inv_mass = 0.0;
	}else{
		inv_mass = 1.0/mass;
	}
	switch(shape->id){
		case exstar::Shape::ID::AABB:
			shape->vertices->add(new Vector2d(0,0));
			shape->vertices->add(new Vector2d(shape->w,0));
			shape->vertices->add(new Vector2d(shape->w,shape->h));
			shape->vertices->add(new Vector2d(0,shape->h));
			break;
	}
	this->shape = shape;
	force = new exstar::Vector2d();
	updateCollider();
}

void exstar::Body::Update(double deltaTime){
	*position += *velocity*deltaTime;
	*position += *force*deltaTime;
	updateCollider();
}

void exstar::Body::applyForce(exstar::Vector2d force){
	*this->force += force;
}

void exstar::Body::applyForce(int x,int y){
	*this->force += exstar::Vector2d(x,y);
}

void exstar::Body::updateCollider(){
	switch(shape->id){
		case exstar::Shape::ID::AABB:
			this->testCollider = exstar::TestCollider(shape->w,shape->h,position->x,position->y);
			break;
		case exstar::Shape::ID::Circle:
			this->testCollider = exstar::TestCollider(shape->r*2.0,shape->r*2.0,(position->x-shape->r),(position->y-shape->r));
			break;
		case exstar::Shape::ID::Polygon:
			exstar::Vector2d min = exstar::Vector2d(FLT_MAX,FLT_MAX);
			exstar::Vector2d max = exstar::Vector2d(-FLT_MAX,-FLT_MAX);
			for(int i = 0;i < shape->vertices->size;i++){
				exstar::Vector2d point = *shape->vertices->get(i)+*position;
				if(point.x < min.x){
					min.x = point.x;
				}else if(point.x > max.x){
					max.x = point.x;
				}
				if(point.y < min.y){
					min.y = point.y;
				}else if(point.y > max.y){
					max.y = point.y;
				}
			}
			this->testCollider = exstar::TestCollider(max.x-min.x,max.y-min.y,min.x,min.y);
			break;
	}
}
