#include "Exstar/Physics/Engine.h"
#include "Exstar/Physics/EngineCollision.h"
#include "Exstar/Utils/Exception.h"
#include "Exstar/Utils/Math.h"

exstar::Vector2d exstar::physics::Engine::GRAVITY      = exstar::Vector2d(0,9.81);
bool  exstar::physics::Engine::PERFORMANCE_MODE        = true ;
bool  exstar::physics::Engine::VERTICAL_FRICTION       = false;
float exstar::physics::Engine::CORRECTION_PERCENT      = 0.5  ;
float exstar::physics::Engine::CORRECTION_ALLOWANCE    = 0.00 ;
int   exstar::physics::Engine::FRAMERATE               = 0    ;

exstar::physics::Engine::Engine(int frameRate){
	exstar::physics::Engine::FRAMERATE = frameRate;
	std::cout << "===================================================================" << std::endl;
	std::cout << "= Warning - PolygonvsPolygon collisions are NOT working right now =" << std::endl;
	std::cout << "===================================================================" << std::endl << std::endl;
}

void exstar::physics::Engine::add(exstar::physics::Body* body){
	bodies->add(body);
}

exstar::physics::Body* exstar::physics::Engine::getById(std::string id){
	for(int i = 0; i < bodies->size; i++){
		if(bodies->get(i)->id == id){
			return bodies->get(i);
		}
	}
	throw exstar::exception("exstar::Engine::getById - No Such ID: " + id);
}

void exstar::physics::Engine::removeById(std::string id){
	for(int i = 0; i < bodies->size; i++){
		if(bodies->get(i)->id == id){
			bodies->remove(i);
		}
	}
	throw exstar::exception("exstar::Engine::getById - No Such ID: " + id);
}

void exstar::physics::Engine::Update(){
	float deltaTime = 1.0/exstar::physics::Engine::FRAMERATE;
	//Check if in Performance Mode
	if(!exstar::physics::Engine::PERFORMANCE_MODE){
		//Performance Mode is disabled
		//Update all bodies
		for(int a = 0; a < bodies->size; a++){
			exstar::physics::Body* current = bodies->get(a);
			current->Update(deltaTime);
		}
		//check for colisions
		for(int a = 0; a < bodies->size; a++){
			exstar::physics::Body* current = bodies->get(a);
			if(current->enabled){
				//Check Broadphase Collision with dublicate culling
				for(int b = a; b < bodies->size; b++){
					if(a != b){
						exstar::physics::Body* looking = bodies->get(b);
						checkCollision(current,looking);
					}
				}
			}
			current->force->set(0, 0);
		}
	}else{
		//Performance Mode is enabled
		//Update and check for collsions
		for(int a = 0; a < bodies->size; a++){
			exstar::physics::Body* current = bodies->get(a);
			current->Update(deltaTime);
			if(current->enabled){
				//Check Broadphase Collision
				for(int b = 0; b < bodies->size; b++){
					if(a != b){
						exstar::physics::Body* looking = bodies->get(b);
						checkCollision(current,looking);
					}
				}
			}
			current->force->set(0, 0);
		}			
	}
}
void exstar::physics::Engine::checkCollision(exstar::physics::Body* current, exstar::physics::Body* looking){
	if(looking->enabled){
		if(current->layer == looking->layer && !(current->inv_mass == 0.0 && looking->inv_mass == 0.0)){
			if(exstar::physics::TestCollider::CheckCollision(&current->testCollider, &looking->testCollider)){
				//Possible Collision
				collision = exstar::physics::PCollision{current, looking};
				switch(current->shape->id){

					case exstar::physics::Shape::ID::AABB:
						switch(looking->shape->id){
							case exstar::physics::Shape::ID::AABB:
								//AABBvsAABB
								if(exstar::physics::EngineCollision::AABBvsAABB(&collision)){
									HandleCollision(&collision);
								}
								break;

							case exstar::physics::Shape::ID::Circle:
								//AABBvsCircle
								if(exstar::physics::EngineCollision::AABBvsCircle(&collision)){
									HandleCollision(&collision);
								}
								break;

							case exstar::physics::Shape::ID::Polygon:
								//AABBvsPolygon
								if(exstar::physics::EngineCollision::PolygonvsPolygon(&collision)){
									HandleCollision(&collision);
								}
								break;
						}
						break;

					case exstar::physics::Shape::ID::Circle:
						switch(looking->shape->id){
								case exstar::physics::Shape::ID::AABB:
									//CirclevsAABB
									if(exstar::physics::EngineCollision::AABBvsCircle(&collision)){
										collision.normal *= -1;
										HandleCollision(&collision);
									}
									break;

								case exstar::physics::Shape::ID::Circle:
									//CirclevsCircle
									if(exstar::physics::EngineCollision::CirclevsCircle(&collision)){
										HandleCollision(&collision);
									}
									break;

								case exstar::physics::Shape::ID::Polygon:
									//CirclevsPolygon
									if(exstar::physics::EngineCollision::CirclevsPolygon(&collision)){
										collision.normal *= -1;
										HandleCollision(&collision);
									}
									break;
							}
						break;
					
					case exstar::physics::Shape::ID::Polygon:
						switch(looking->shape->id){
								case exstar::physics::Shape::ID::AABB:
									//PolygonvsAABB
									if(exstar::physics::EngineCollision::PolygonvsPolygon(&collision)){
										HandleCollision(&collision);
									}
									break;

								case exstar::physics::Shape::ID::Circle:
									//PolygonvsCircle
									if(exstar::physics::EngineCollision::CirclevsPolygon(&collision)){
										HandleCollision(&collision);
									}
									break;

								case exstar::physics::Shape::ID::Polygon:
									//PolygonvsPolygon
									if(exstar::physics::EngineCollision::PolygonvsPolygon(&collision)){
										HandleCollision(&collision);
									}
									break;
							}
						break;
				}
			}
		}
	}
}
void exstar::physics::Engine::HandleCollision(exstar::physics::PCollision* collision){
	Impulse(collision);
	PositionalCorrection(collision);
}

void exstar::physics::Engine::Impulse(exstar::physics::PCollision* collision){
	exstar::physics::Body* A = collision->A;
	exstar::physics::Body* B = collision->B;
	exstar::Vector2d normal  = exstar::Vector2d((float)collision->normal.x,(float)collision->normal.y);
	float penetration = collision->penetration;

	if(std::isnan(normal.x)){
		normal.x = 0;
	}
	if(std::isnan(normal.y)){
		normal.y = 0;
	}

	exstar::Vector2d rv  = *B->velocity - *A->velocity;

	float velAlongNormal = exstar::Vector2d::dot(rv,normal);

	if(velAlongNormal > 0){
		return;
	}

	float e = std::max(A->restitution, B->restitution);

	float j = -(1.0 + e)*velAlongNormal;
	j /= A->inv_mass + B->inv_mass;
	exstar::Vector2d impulse = normal*j;
	float sum_mass = A->mass + B->mass;
	float ratio = A->mass / sum_mass;
	if(std::isnan(ratio)){
		ratio = 1.0;
	}
	if(A->inv_mass != 0){
		*A->velocity -= (impulse*A->inv_mass)*ratio;
	}
	ratio = B->mass / sum_mass;
	if(B->inv_mass != 0){
		*B->velocity += (impulse*B->inv_mass)*ratio;
	}

	//FRICTION
	rv = *B->velocity - *A->velocity;

	exstar::Vector2d tangent = rv - (normal * exstar::Vector2d::dot(rv,normal));
	tangent = exstar::Vector2d::normalize(tangent);

	float jt = exstar::Vector2d::dot(rv,tangent) *-1;
	jt /= A->inv_mass + B->inv_mass;

	float mu = sqrt(pow(A->staticFriction,2) + pow(B->staticFriction,2));

	exstar::Vector2d frictionImpulse;
	if(abs(jt) < j * mu){
		frictionImpulse = tangent*jt;
	}else{
		float dynamicFriction = sqrt(pow(A->dynamicFriction,2) + pow(B->dynamicFriction,2));
		frictionImpulse = tangent * -j * dynamicFriction;
	}
	if(!exstar::physics::Engine::VERTICAL_FRICTION){
		frictionImpulse.y = 0;
	}
	*A->velocity -= frictionImpulse * A->inv_mass;
	*B->velocity += frictionImpulse * B->inv_mass;
}


void exstar::physics::Engine::PositionalCorrection(exstar::physics::PCollision* collision){
	exstar::physics::Body* A = collision->A;
	exstar::physics::Body* B = collision->B;
	float penetration        = collision->penetration;
	exstar::Vector2d normal  = exstar::Vector2d((float)collision->normal.x, (float)collision->normal.y);

	if(std::isnan(normal.x)){
		normal.x = 0;
	}
	if(std::isnan(normal.y)){
		normal.y = 0;
	}

	exstar::Vector2d correction = (normal*(std::max(penetration - exstar::physics::Engine::CORRECTION_ALLOWANCE,0.0f)/(A->inv_mass + B->inv_mass)))*exstar::physics::Engine::CORRECTION_PERCENT;

	if(A->inv_mass != 0){
		*A->position -= correction*A->inv_mass;
	}
	if(B->inv_mass != 0){
		*B->position += correction*B->inv_mass;
	}
}
