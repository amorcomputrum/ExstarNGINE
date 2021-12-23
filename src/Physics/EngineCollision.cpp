#include "Exstar/Physics/EngineCollision.h"
#include "Exstar/Utils/Math.h"

bool exstar::EngineCollision::CirclevsCircle(exstar::PCollision collision){
	int r1 = collision.A->shape->r;
	int r2 = collision.B->shape->r;
	int r = r1+r2;
	r *= r;
	if(r < pow(collision.A->position.x + collision.B->position.x,2) + pow(collision.A->position.y + collision.B->position.y,2)){
		collision.normal = collision.B->position - collision.A->position;
		if(collision.normal.magnitude() != 0){
			collision.penetration = r - collision.normal.magnitude();
			collision.normal = collision.normal/collision.normal.magnitude();
		}else{
			collision.penetration = r1;
			collision.normal = exstar::Vector2d(1,0);
		}
	}
}
bool exstar::EngineCollision::CirclevsPolygon(exstar::PCollision collision){
	exstar::Body* A;
	exstar::Body* B;
	if(collision.A->shape->id == exstar::Shape::ID::Circle){
		A = collision.A;
		B = collision.B;
	}else{
		A = collision.B;
		B = collision.A;
	}
}