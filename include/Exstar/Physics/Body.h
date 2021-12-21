#ifndef Body_h
#define Body_h
	#include "Exstar/Utils/Vector2d.h"
	#include "Exstar/Physics/Shape.h"

	namespace exstar{
		class Body{
		public:
			exstar::Vector2d position;
			float rotation;

			exstar::Vector2d velocity;
			float angular_vel;

			exstar::Vector2d force;
			float torque;

			float mass;
			float inertia;

			float coeff_friction = 0.2;
			float coeff_restitution = 0.2;

			exstar::Vector2d gravity = exstar::Vector2d(0,9.8);

			exstar::Shape shape;
			Body(exstar::Vector2d position,float rotation,int mass,exstar::Shape shape);
			void Update(double deltaTime);
		};
	}
	#include "Exstar/Physics/Body.cpp"
#endif