#include "Exstar/Physics/Engine.h"
#include "Exstar/Physics/EngineCollision.h"
#include "Exstar/Utils/Exception.h"
#include "Exstar/Utils/Math.h"

exstar::Engine::Engine(){
}

void exstar::Engine::add(exstar::Body* body){
	bodies->add(body);
}
exstar::Body* exstar::Engine::getById(std::string id){
	for(int i = 0;i < bodies->size;i++){
		if(bodies->get(i)->id == id){
			return bodies->get(i);
		}
	}
	throw exstar::exception("exstar::Engine::getById - No Such ID: " + id);
}
void exstar::Engine::Update(double deltaTime){
	for(int a = 0;a < bodies->size;a++){
		//update body
		bodies->get(a)->Update(deltaTime);
		exstar::Body* current = bodies->get(a);
		//Check Broadphase Collision
		for(int b = 0;b < bodies->size;b++){
			if(a != b){
				exstar::Body* looking = bodies->get(b);
				if(exstar::TestCollider::CheckCollision(&current->testCollider,&looking->testCollider)){
					//Possible Collision
					collision = exstar::PCollision{current,looking};
					switch(current->shape->id){
						case exstar::Shape::ID::AABB:
							switch(looking->shape->id){
								case exstar::Shape::ID::AABB:
									//AABBvsAABB
									if(exstar::EngineCollision::AABBvsAABB(&collision)){
										HandleCollision(&collision);
									}
									break;
								case exstar::Shape::ID::Circle:
									//AABBvsCircle
									if(exstar::EngineCollision::AABBvsCircle(&collision)){
										HandleCollision(&collision);
									}
									break;
								case exstar::Shape::ID::Polygon:
									//AABBvsPolygon
									if(exstar::EngineCollision::PolygonvsPolygon(&collision)){
										HandleCollision(&collision);
									}
									break;
							}
							break;
						case exstar::Shape::ID::Circle:
							switch(looking->shape->id){
									case exstar::Shape::ID::AABB:
										//CirclevsAABB
										if(exstar::EngineCollision::AABBvsCircle(&collision)){
											collision.normal *= -1;
											HandleCollision(&collision);
										}
										break;
									case exstar::Shape::ID::Circle:
										//CirclevsCircle
										if(exstar::EngineCollision::CirclevsCircle(&collision)){
											HandleCollision(&collision);
										}
										break;
									case exstar::Shape::ID::Polygon:
										//CirclevsPolygon
										if(exstar::EngineCollision::CirclevsPolygon(&collision)){
											HandleCollision(&collision);
										}
										break;
								}
							break;
						
						case exstar::Shape::ID::Polygon:
							switch(looking->shape->id){
									case exstar::Shape::ID::AABB:
										//PolygonvsAABB
										if(exstar::EngineCollision::PolygonvsPolygon(&collision)){
											HandleCollision(&collision);
										}
										break;
									case exstar::Shape::ID::Circle:
										//PolygonvsCircle
										if(exstar::EngineCollision::CirclevsPolygon(&collision)){
											HandleCollision(&collision);
										}
										break;
									case exstar::Shape::ID::Polygon:
										//PolygonvsPolygon
										if(exstar::EngineCollision::PolygonvsPolygon(&collision)){
											collision.normal *= -1;
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
}
void exstar::Engine::HandleCollision(exstar::PCollision* collision){
	Impulse(collision);
	PositionalCorrection(collision);
}
void exstar::Engine::Impulse(exstar::PCollision* collision){
	exstar::Body* A = collision->A;
	exstar::Body* B = collision->B;
	float penetration = collision->penetration;
	exstar::Vector2d normal = exstar::Vector2d((float)collision->normal.x,(float)collision->normal.y);
	exstar::Vector2d rv = *B->velocity - *A->velocity;

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
	if(A->inv_mass != 0){
		*A->velocity -= (impulse*A->inv_mass)*ratio;
	}
	ratio = B->mass / sum_mass;
	if(B->inv_mass != 0){
		*B->velocity += (impulse*B->inv_mass)*ratio;
	}
	
	
}

void exstar::Engine::PositionalCorrection(exstar::PCollision* collision){
	exstar::Body* A = collision->A;
	exstar::Body* B = collision->B;
	float penetration = collision->penetration;
	exstar::Vector2d normal = exstar::Vector2d((float)collision->normal.x,(float)collision->normal.y);

	const float percent = 0.025;
	const float slop = 0.01;
	exstar::Vector2d correction = (normal*(std::max(penetration - slop,0.0f) / (A->inv_mass + B->inv_mass)))*percent;
	if(A->inv_mass != 0){
		*A->position -= correction*A->inv_mass;
	}
	if(B->inv_mass != 0){
		*B->position += correction*B->inv_mass;
	}
}