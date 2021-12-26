#include "Exstar/Physics/TestCollider.h"

bool exstar::TestCollider::CheckCollision(exstar::Vector2d* pos1,exstar::TestCollider t1,exstar::Vector2d* pos2,exstar::TestCollider t2){
	int x1 = pos1->x;
	int y1 = pos1->y;
	int w1 = t1.w;
	int h1 = t1.h;

	int x2 = pos2->x;
	int y2 = pos2->y;
	int w2 = t2.w;
	int h2 = t2.h;

	return ((((x1+w1 > x2) && x1 < x2) || ((x1 < x2+w2) && (x1+w1 > x2))) && (((y1+h1 > y2) && y1 < y2) || ((y1 < y2+h2) && (y1+h1 > y2))));
}