#include "Exstar/Physics/EngineCollision.h"
#include "Exstar/Utils/Math.h"
#include "Exstar/Physics/DetectCollision.h"

bool exstar::EngineCollision::CirclevsCircle(exstar::PCollision collision){
	int r1 = collision.A->shape->r;
	int r2 = collision.B->shape->r;
	int r = r1+r2;
	r *= r;
	if(r < pow(collision.A->position->x + collision.B->position->x,2) + pow(collision.A->position->y + collision.B->position->y,2)){
		collision.normal = *collision.B->position - *collision.A->position;
		if(collision.normal.magnitude() != 0){
			collision.penetration = r - collision.normal.magnitude();
			collision.normal = collision.normal/collision.normal.magnitude();
		}else{
			collision.penetration = r1;
			collision.normal = exstar::Vector2d(1,0);
		}
		return true;
	}
	return false;
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
	bool inside = false;
	bool detected = false;
	exstar::Vector2d closest = *B->shape->vertices->get(0) + *B->position;
	for(int i = 0; i < B->shape->vertices->size;i++){
			exstar::Vector2d point = *B->shape->vertices->get(i) + *B->position;
			if((pow(A->position->x-closest.x,2) + pow(A->position->y-closest.y,2)) > (pow(A->position->x-point.x,2) + pow(A->position->y-point.y,2))){
				closest = point;
			}
			int next = i+1;
			if(next == B->shape->vertices->size) next = 0;
			exstar::Vector2d* vc = B->shape->vertices->get(i);
			exstar::Vector2d* vn = B->shape->vertices->get(i+1);
			detected = exstar::DetectCollision::LinevsCircle(vc->x,vc->y,vn->x,vn->y,A->position->x,A->position->y,A->shape->r);
			if(detected) break;
			if (((vc->y >= A->position->y && vn->y < A->position->y) || (vc->y < A->position->y && vn->y >= A->position->y)) &&
         (A->position->x < (vn->x-vc->x)*(A->position->y-vc->y) / (vn->y-vc->y)+vc->x)) {
            inside = !inside;
    }
	}
	if(detected || inside){
		if(inside){
			collision.normal = (*A->position - closest) * -1;
			collision.penetration = (((*A->position-closest)*-1) + A->shape->r).magnitude();
		}else{
			collision.penetration = (((*A->position-closest)*-1) + A->shape->r).magnitude();
			collision.normal = *A->position-closest;
		}
		return true;
	}
	return false;
}
