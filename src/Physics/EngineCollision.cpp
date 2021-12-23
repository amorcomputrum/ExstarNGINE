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
	for(int i = 0; i < B->shape->vertices->size;i++){
			int next = i+1;
			if(next == B->shape->vertices->size) next = 0;
			exstar::Vector2d* vc = B->shape->vertices->get(i);
			exstar::Vector2d* vn = B->shape->vertices->get(i+1);
			detected = exstar::DetectCollision::LinevsCircle(vc->x,vc->y,vn->x,vn->y,A->position->x,A->position->y,A->shape->r);
			if(detected) break;
	}
	if(PolygonvsPoint(B->shape->vertices,A->position->x,A->position->y)) inside=true;
	if(detected || inside){
		//Collision Detected
		//find closest point
		exstar::Vector2d closest = *B->shape->vertices->get(0) + *B->position;
		for(int i = 0; i < B->shape->vertices->size;i++){
			exstar::Vector2d point = *B->shape->vertices->get(i) + *B->position;
			if((pow(A->position->x-closest.x,2) + pow(A->position->y-closest.y,2)) > (pow(A->position->x-point.x,2) + pow(A->position->y-point.y,2))){
				closest = point;
			}
		}
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
bool exstar::EngineCollision::PolygonvsPoint(exstar::ArrayList<exstar::Vector2d*>* vertices, int px, int py) {
  bool collision = false;
  int next = 0;
  for (int current=0; current<vertices->size; current++) {
    next = current+1;
    if (next == vertices->size) next = 0;

    exstar::Vector2d* vc = vertices->get(current);
    exstar::Vector2d* vn = vertices->get(next);

    if (((vc->y >= py && vn->y < py) || (vc->y < py && vn->y >= py)) &&
         (px < (vn->x-vc->x)*(py-vc->y) / (vn->y-vc->y)+vc->x)) {
            collision = !collision;
    }
  }
  return collision;
}