#include "Exstar/Physics/PCollision.h"
namespace exstar{
	struct EngineCollision{
		static bool AABBvsAABB(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2);
		static bool CirclevsCircle(exstar::PCollision collision);
		static bool CirclevsPolygon(exstar::PCollision collision);
	};
}