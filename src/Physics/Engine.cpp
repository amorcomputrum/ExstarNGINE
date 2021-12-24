#include "Exstar/Physics/Engine.h"
#include "Exstar/Utils/Math.h"

void exstar::Engine::Impulse(exstar::PCollision* collision){
	exstar::Body* A = collision->A;
	exstar::Body* B = collision->B;
	float penetration = collision->penetration;
	exstar::Vector2d normal = exstar::Vector2d((float)collision->normal->x,(float)collision->normal->y);
	exstar::Vector2d rv = *B->velocity - *A->velocity;

	float velAlongNormal = exstar::Vector2d::dot(rv,normal);

	if(velAlongNormal > 0){
		return;
	}

	float e = std::min(A->restitution, B->restitution);

	float j = -(1.0 + e)*velAlongNormal;
	j /= A->inv_mass + B->inv_mass;
	std::cout << std::endl << j << std::endl;
	exstar::Vector2d impulse = normal*j;
	*A->velocity -= impulse*A->inv_mass;
	*B->velocity += impulse*B->inv_mass;
}

void exstar::Engine::PositionalCorrection(exstar::PCollision* collision){
	exstar::Body* A = collision->A;
	exstar::Body* B = collision->B;
	float penetration = collision->penetration;
	exstar::Vector2d* normal = collision->normal;

	const float percent = 0.2;
	const float slop = 0.01;
	exstar::Vector2d correction = (*normal*(std::max(penetration - slop,0.0f) / (A->inv_mass + B->inv_mass)))*percent;
	*A->position -= correction*A->inv_mass;
	*B->position += correction*B->inv_mass;
}