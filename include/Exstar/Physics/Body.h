#ifndef EXSTAR_BODY_H
#define EXSTAR_BODY_H
#include "Exstar/Physics/Shape.h"
#include "Exstar/Physics/Box.h"
#include "Exstar/Physics/Circle.h"
#include "Exstar/Physics/ConvexPolygon.h"
#include "Exstar/Utils/Vector2d.h"
#include "Exstar/Physics/TestCollider.h"
namespace exstar{
	namespace physics{
		class Body{
		public:
			exstar::physics::Shape* shape;
			float restitution;
			int mass;
			float inv_mass;
			exstar::physics::TestCollider testCollider;
			exstar::Vector2d* position;
			exstar::Vector2d* velocity;
			exstar::Vector2d* force;
			std::string id;
			Body();
			Body(exstar::Vector2d position,float restitution,int mass,exstar::physics::Shape* shape,std::string id);
			Body(exstar::Vector2d position,exstar::Vector2d velocity,float restitution,int mass,exstar::physics::Shape* shape,std::string id);
			void Update(double deltaTime);
			void applyForce(exstar::Vector2d force);
			void applyForce(int x,int y);
			void updateCollider();
		};
	}
}
#endif
