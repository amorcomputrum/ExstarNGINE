#include <float.h>
#include <algorithm>

#include "Exstar/Physics/EngineCollision.h"
#include "Exstar/Utils/Math.h"
#include "Exstar/Physics/DetectCollision.h"

bool exstar::EngineCollision::AABBvsAABB(exstar::PCollision* collision){
	exstar::Body* A = collision->A;
	exstar::Body* B = collision->B;

	exstar::Vector2d n = *collision->B->position - *collision->A->position;

	float a_extent = ((A->position->x + A->shape->w) - A->position->x)/2;
	float b_extent = ((B->position->x + B->shape->w) - B->position->x)/2;

	float x_overlap = a_extent + b_extent - abs(n.x);
	if(x_overlap > 0){
		a_extent = ((A->position->y + A->shape->h) - A->position->y)/2;
		a_extent = ((B->position->y + B->shape->h) - B->position->y)/2;

		float y_overlap = a_extent + b_extent - abs(n.y);
		if(x_overlap>y_overlap){
			if(n.x < 0){
				collision->normal->set(-1,0);
			}else{
				collision->normal->set(0,0);
			}
			collision->penetration = x_overlap;
			return true;
		}else{
			if(n.y < 0){
				collision->normal->set(0,-1);
			}else{
				collision->normal->set(0,1);
			}
			collision->penetration = y_overlap;
			return true;
		}

	}
	return false;
}
bool exstar::EngineCollision::AABBvsCircle(exstar::PCollision* collision){
	exstar::Body* A;
	exstar::Body* B;
	if(collision->A->shape->id == exstar::Shape::ID::Circle){
		A = collision->B;
		B = collision->A;
	}else{
		A = collision->A;
		B = collision->B;
	}

	exstar::Vector2d n = *B->position - *A->position;
	exstar::Vector2d closest = n;

	float x_extent = ((A->position->x + A->shape->w) - A->position->x)/2;
	float y_extent = ((A->position->y + A->shape->h) - A->position->y)/2;

	closest.x = std::clamp(-x_extent,x_extent,(float)closest.x);
	closest.y = std::clamp(-y_extent,y_extent,(float)closest.y);
	bool inside = false;
	if(n.x == closest.x && n.y == closest.y){
		inside = true;

		if(abs(n.x) > abs(n.y)){
			if(closest.x > 0){
				closest.x = x_extent;
			}else{
				closest.x = -x_extent;
			}
		}else{
			if(closest.y > 0){
				closest.y = y_extent;
			}else{
				closest = -y_extent;
			}
		}
		exstar::Vector2d normal = n - closest;
		double d = normal.sqrMagnitude();
		double r = B->shape->r;

		if(d > r * r && !inside){
			return false;
		}

		d = sqrt(d);
		if(inside){
			collision->normal->set(n*-1);
			collision->penetration = r-d;
		}else{
			collision->normal->set(n);
			collision->penetration = r-d;
		}
		return true;
	}

}
bool exstar::EngineCollision::CirclevsCircle(exstar::PCollision* collision){
	int r1 = collision->A->shape->r;
	int r2 = collision->B->shape->r;
	int r = r1+r2;
	r *= r;
	if(r < pow(collision->A->position->x + collision->B->position->x,2) + pow(collision->A->position->y + collision->B->position->y,2)){
		collision->normal->set(*collision->B->position - *collision->A->position);
		if(collision->normal->magnitude() != 0){
			collision->penetration = r - collision->normal->magnitude();
			collision->normal->set(*collision->normal/collision->normal->magnitude());
		}else{
			collision->penetration = r1;
			collision->normal->set(exstar::Vector2d(1,0));
		}
		return true;
	}
	return false;
}
bool exstar::EngineCollision::CirclevsPolygon(exstar::PCollision* collision){
	exstar::Body* A;
	exstar::Body* B;
	if(collision->A->shape->id == exstar::Shape::ID::Circle){
		A = collision->A;
		B = collision->B;
	}else{
		A = collision->B;
		B = collision->A;
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
			collision->normal->set((*A->position - closest) * -1);
			collision->penetration = (((*A->position-closest)*-1) + A->shape->r).magnitude();
		}else{
			collision->penetration = (((*A->position-closest)*-1) + A->shape->r).magnitude();
			collision->normal->set(*A->position-closest);
		}
		return true;
	}
	return false;
}
bool exstar::EngineCollision::PolygonvsPolygon(exstar::PCollision* collision){//from here
	exstar::Body* A = collision->A;
	exstar::Body* B = collision->B;
	exstar::Vector2d axis;
	bool intersect = true;
	for (int i = 0; i <  A->shape->vertices->size; ++i){
		exstar::Vector2d current = *A->shape->vertices->get(i)+*A->position;
		exstar::Vector2d next;
		if(i+1 < A->shape->vertices->size){
			next = *A->shape->vertices->get(i+1)+*A->position;
		}else{
			next = *A->shape->vertices->get(0)+*A->position;
		}
		exstar::Vector2d edge = next - current;
		axis = exstar::Vector2d(-edge.y,edge.x);
		float aMax = -FLT_MAX;
		float aMin = FLT_MAX;
		float bMax = -FLT_MAX;
		float bMin = FLT_MAX;
		int limit = std::max(A->shape->vertices->size,B->shape->vertices->size);
		for(int v = 0; v < limit;v++){
			if(v < A->shape->vertices->size){
				float proj = exstar::Vector2d::dot(axis,*A->shape->vertices->get(v)+*A->position);
				if(proj < aMin) aMin = proj;
				if(proj > aMax) aMax = proj;
			}
			if(v < B->shape->vertices->size){
				float proj = exstar::Vector2d::dot(axis,*B->shape->vertices->get(v)+*B->position);
				if(proj < bMin) bMin = proj;
				if(proj > bMax) bMax = proj;
			}
		}
		if(IntervalDistance(exstar::Vector2d(aMin,aMax),exstar::Vector2d(bMin,bMax)) > 0){
			intersect = false;
		}
	}
	if(intersect){	
			exstar::Vector2d d = *B->position - *A->position;
			collision->normal->set(exstar::Vector2d::normalize(d));
			collision->penetration = d.magnitude();
			return true;
	}
	return false;
}

float exstar::EngineCollision::IntervalDistance(exstar::Vector2d a,exstar::Vector2d b){
	if(a.x < b.x){
		return b.x - a.y;
	}else{
		return a.x - b.y;
	}
}