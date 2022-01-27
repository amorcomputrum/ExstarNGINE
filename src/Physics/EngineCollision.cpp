#include <float.h>
#include <algorithm>

#include "Exstar/Physics/DetectCollision.h"
#include "Exstar/Utils/Math.h"

#include "Exstar/Physics/EngineCollision.h"

bool exstar::physics::EngineCollision::AABBvsAABB(exstar::physics::PCollision* collision){
	exstar::physics::Body* A = collision->A;
	exstar::physics::Body* B = collision->B;

	exstar::Vector2d n = (*collision->B->position + exstar::Vector2d(B->shape->w/2,B->shape->h/2))- (*collision->A->position+ exstar::Vector2d(A->shape->w/2,A->shape->h/2));

	float a_extent = A->shape->w/2;
	float b_extent = B->shape->w/2;

	float x_overlap = a_extent + b_extent - abs(n.x);
	if(x_overlap >= 0){
		a_extent = A->shape->h/2;
		b_extent = B->shape->h/2;

		float y_overlap = a_extent + b_extent - abs(n.y);
		if(y_overlap >= 0){
			if(x_overlap < y_overlap){
				if(n.x < 0){
					collision->normal.set(-1, 0);
				}else{
					collision->normal.set(0, 0 );
				}
				collision->penetration = x_overlap;
				return true;
			}else{
				if(n.y < 0){
					collision->normal.set(0, -1);
				}else{
					collision->normal.set(0, 1 );
				}
				collision->penetration = y_overlap;
				return true;
			}
		}
		
	}
	return false;
}

bool exstar::physics::EngineCollision::AABBvsCircle(exstar::physics::PCollision* collision){
	exstar::physics::Body* A;
	exstar::physics::Body* B;
	if(collision->A->shape->id == exstar::physics::Shape::ID::Circle){
		A = collision->B;
		B = collision->A;
	}else{
		A = collision->A;
		B = collision->B;
	}

	exstar::Vector2d n = *B->position - (*A->position + exstar::Vector2d(A->shape->w/2.0, A->shape->h/2.0));
	exstar::Vector2d closest = n;

	double x_extent = A->shape->w/2.0;
	double y_extent = A->shape->h/2.0;

	closest.x = std::clamp(closest.x, -x_extent, x_extent);
	closest.y = std::clamp(closest.y, -y_extent, y_extent);

	bool inside = false;

	if(n.x == closest.x && n.y == closest.y){
		inside = true;
		if(abs(n.x) > abs(n.y)){
			if(closest.x > 0){
				closest.x = x_extent ;
			}else{
				closest.x = -x_extent;
			}
		}else{
			if(closest.y > 0){
				closest.y = y_extent ;
			}else{
				closest.y = -y_extent;
			}
		}
	}

	exstar::Vector2d normal = n - closest;
	float d = normal.sqrMagnitude();
	float r = B->shape->r;

	if(d > r*r && !inside){
		return false;
	}
	d = sqrt(d);

	if(inside){
		collision->normal      = exstar::Vector2d::normalize(normal*-1);
		collision->penetration = r - d;
	}else{
		collision->normal      = exstar::Vector2d::normalize(normal   );
		collision->penetration = r - d;
	}
	return true;
}

bool exstar::physics::EngineCollision::CirclevsCircle(exstar::physics::PCollision* collision){
	int r1 = collision->A->shape->r;
	int r2 = collision->B->shape->r;
	exstar::Vector2d n = *collision->B->position - *collision->A->position;
	float r = r1 + r2;

	if(n.sqrMagnitude() >= r*r) return false;

	float d = n.magnitude();

	if(d != 0){
		collision->penetration = r;
		collision->normal.set(n/d);
	}else{
		collision->penetration = r-d;
		collision->normal.set(1, 0);
	}
}

bool exstar::physics::EngineCollision::CirclevsPolygon(exstar::physics::PCollision* collision){
	exstar::physics::Body* A;
	exstar::physics::Body* B;

	if(collision->A->shape->id == exstar::physics::Shape::ID::Circle){
		A = collision->A;
		B = collision->B;
	}else{
		A = collision->B;
		B = collision->A;
	}

	bool inside = false;
	bool detected = false;
	exstar::Vector2d closest = *B->shape->vertices->get(0) + *B->position;
	exstar::Vector2d n;

	for(int i = 0; i < B->shape->vertices->size; i++){
		exstar::Vector2d point = *B->shape->vertices->get(i) + *B->position;
		if((pow(A->position->x - closest.x, 2) + pow(A->position->y - closest.y, 2)) > (pow(A->position->x - point.x, 2) + pow(A->position->y - point.y, 2))){
			closest = point;
		}
		int next = i + 1;
		if(next == B->shape->vertices->size) next = 0;
		exstar::Vector2d vc = *B->shape->vertices->get(i) + *B->position;
		exstar::Vector2d vn;
		if(i + 1 < B->shape->vertices->size){
			vn = *B->shape->vertices->get(i + 1) + *B->position;
		}else{
			vn = *B->shape->vertices->get(0) + *B->position;
		}
		detected = exstar::physics::DetectCollision::LinevsCircle(vc.x, vc.y, vn.x, vn.y, A->position->x, A->position->y, A->shape->r);
		if(detected){
			exstar::Vector2d face = vn - vc;
			n = exstar::Vector2d(face.y, -face.x);
		}
		if(detected) break;
		if (((vc.y >= A->position->y && vn.y < A->position->y) || (vc.y < A->position->y && vn.y >= A->position->y)) &&
			(A->position->x < (vn.x - vc.x)*(A->position->y - vc.y) / (vn.y-  vc.y) + vc.x)) {
         inside = !inside;
 		}
	}

	if(detected || inside){
		if(inside){
			collision->normal.set(exstar::Vector2d::normalize(n)*-1);
			collision->penetration = (((*A->position-closest)*-1) + A->shape->r).magnitude();
		}else{
			collision->penetration = (((*A->position-closest)*-1) + A->shape->r).magnitude();
			collision->normal.set(exstar::Vector2d::normalize(n)   );
		}
		return true;
	}
	return false;
}

bool exstar::physics::EngineCollision::PolygonvsPolygon(exstar::physics::PCollision* collision){
	exstar::physics::Body* A = collision->A;
	exstar::physics::Body* B = collision->B;

	exstar::Vector2d axis;
	bool intersect = true;

	for (int i = 0; i <  A->shape->vertices->size + B->shape->vertices->size; i++){
		exstar::Vector2d current;
		exstar::Vector2d next;

		if(i < A->shape->vertices->size){
			current = *A->shape->vertices->get(i) + *A->position    ;
			if(i + 1 < A->shape->vertices->size){
				next = *A->shape->vertices->get(i + 1) + *A->position;
			}else{
				next = *A->shape->vertices->get(0) + *A->position    ;
			}
		}else{
			current = *B->shape->vertices->get(i - A->shape->vertices->size) + *B->position;
			if((i-A->shape->vertices->size) + 1 < B->shape->vertices->size){
				next = *B->shape->vertices->get((i-A->shape->vertices->size) + 1) + *B->position;
			}else{
				next = *B->shape->vertices->get(0) + *B->position;
			}
		}

		exstar::Vector2d edge = next - current;
		axis = exstar::Vector2d(-edge.y, edge.x);
		
		float aMax = -FLT_MAX;
		float aMin = FLT_MAX ;
		float bMax = -FLT_MAX;
		float bMin = FLT_MAX ;

		int limit = std::max(A->shape->vertices->size, B->shape->vertices->size);
		for(int v = 0; v < limit; v++){
			if(v < A->shape->vertices->size){
				float proj = exstar::Vector2d::dot(axis, *A->shape->vertices->get(v) + *A->position);
				if(proj < aMin) aMin = proj;
				if(proj > aMax) aMax = proj;
			}
			if(v < B->shape->vertices->size){
				float proj = exstar::Vector2d::dot(axis, *B->shape->vertices->get(v) + *B->position);
				if(proj < bMin) bMin = proj;
				if(proj > bMax) bMax = proj;
			}
		}

		if(IntervalDistance(exstar::Vector2d(aMin, aMax), exstar::Vector2d(bMin, bMax)) > 0){
			intersect = false;
		}
	}
	
	if(intersect){	
			exstar::Vector2d d     = *B->position - *A->position;
			collision->normal.set(exstar::Vector2d::normalize(d));
			collision->penetration = d.magnitude();
			return true;
	}
	return false;
}
float exstar::physics::EngineCollision::IntervalDistance(exstar::Vector2d a, exstar::Vector2d b){
	if(a.x < b.x){
		return b.x - a.y;
	}else{
		return a.x - b.y;
	}
}