#pragma once

#include "Exstar/Utils/Vector2d.h"

namespace exstar{
	namespace physics{
		class TestCollider{
		public:
			float w,h,x,y;
			TestCollider();
			TestCollider(float w, float h, float x, float y);
			static bool CheckCollision(exstar::physics::TestCollider* t1, exstar::physics::TestCollider* t2);
		};
	}
}
