#ifndef Body_H
#define Body_H
	#include "Exstar/Physics/Shape.h"
	#include "Exstar/Physics/Box.h"
	#include "Exstar/Physics/Circle.h"
	#include "Exstar/Physics/ConvexPolygon.h"
	#include "Exstar/Utils/Vector2d.h"
	#include "Exstar/Physics/TestCollider.h"
	namespace exstar{
		class Body{
		public:
			exstar::Shape* shape;
			float restitution;
			int mass;
			float inv_mass;
			exstar::TestCollider testCollider;
			exstar::Vector2d* position;
			exstar::Vector2d* velocity;
			std::string id;
			Body();
			Body(exstar::Vector2d position,float restitution,int mass,exstar::Shape* shape,std::string id);
			Body(exstar::Vector2d position,exstar::Vector2d velocity,float restitution,int mass,exstar::Shape* shape,std::string id);
			void Update(double deltaTime);
			void updateCollider();
		};
		#include "Exstar/Physics/Body.cpp"
	}
#endif
