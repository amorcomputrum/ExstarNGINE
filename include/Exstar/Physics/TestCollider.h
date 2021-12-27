#ifndef EXSTAR_TESTCOLLIDER_H
#define EXSTAR_TESTCOLLIDER_H
	#include "Exstar/Utils/Vector2d.h"
	namespace exstar{
		class TestCollider{
		public:
			float w,h,x,y;
			TestCollider();
			TestCollider(float w,float h,float x,float y);
			static bool CheckCollision(exstar::TestCollider* t1,exstar::TestCollider* t2);
		};
	}
	#include "Exstar/Physics/TestCollider.cpp"
#endif