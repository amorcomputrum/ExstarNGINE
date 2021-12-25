#ifndef EngineCollision_H
#define EngineCollision_H
	#include "Exstar/Physics/PCollision.h"
	#include "Exstar/Utils/Vector2d.h"
	namespace exstar{
		class EngineCollision{
		public:
			static bool AABBvsAABB(int x1,int y1,int w1,int h1,int x2,int y2,int w2,int h2);
			static bool CirclevsCircle(exstar::PCollision* collision);
			static bool CirclevsPolygon(exstar::PCollision* collision);
			static bool PolygonvsPolygon(exstar::PCollision* collision);
			static float IntervalDistance(exstar::Vector2d a,exstar::Vector2d b);
			static void Projection(exstar::Vector2d axis, exstar::ArrayList<exstar::Vector2d*>* verts,float* min,float* max);
		};
	}
	#include "Exstar/Physics/EngineCollision.cpp"
#endif