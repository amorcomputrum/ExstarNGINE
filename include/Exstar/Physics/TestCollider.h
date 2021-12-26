#include "Exstar/Utils/Vector2d.h"
namespace exstar{
	struct TestCollider{
		int w,h;
		static bool CheckCollision(exstar::Vector2d* pos1,exstar::TestCollider t1,exstar::Vector2d* pos2,exstar::TestCollider t2);
	};
}