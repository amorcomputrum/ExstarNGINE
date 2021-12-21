#include "Exstar/Physics/Body.h"

exstar::Body::Body(exstar::Vector2d position,float rotation,int mass,exstar::Shape shape){
	this->position = position;
	this->rotation = rotation;
	this->mass = mass;
	this->shape = shape;
	velocity = exstar::Vector2d(0,0);
	angular_vel = 0;
	force = exstar::Vector2d(0,0);
	torque = 0;
	inertia = 0;
}

void exstar::Body::Update(double deltaTime){
	exstar::Vector2d acceleration = force/mass + gravity;
	velocity += acceleration*deltaTime;
	position += velocity*deltaTime;

	angular_vel += torque/inertia*deltaTime;
	rotation += angular_vel*deltaTime;

	force = exstar::Vector2d(0,0);
	torque = 0;
}