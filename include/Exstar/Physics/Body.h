#pragma once

#include "Exstar/Physics/Box.h"
#include "Exstar/Physics/Circle.h"
#include "Exstar/Physics/ConvexPolygon.h"
#include "Exstar/Physics/Shape.h"
#include "Exstar/Physics/TestCollider.h"
#include "Exstar/Utils/Vector2d.h"

namespace exstar{
	namespace physics{
		class Body{
		public:
			exstar::physics::Shape* shape;
			bool hasGravity;
			float restitution;
			int mass;
			int layer = 0;
			float inv_mass;
			float staticFriction  = 1;
			float dynamicFriction = 1;
			bool enabled = true;
			exstar::physics::TestCollider testCollider;
			exstar::Vector2d* position;
			exstar::Vector2d* velocity;
			exstar::Vector2d* force;
			exstar::Vector2d* gravitationalForce;
			std::string id;
			Body();
			Body(exstar::Vector2d position, float restitution, int mass, exstar::physics::Shape* shape, std::string id, bool hasGravity);
			Body(exstar::Vector2d position, exstar::Vector2d velocity, float restitution, int mass, exstar::physics::Shape* shape, std::string id, bool hasGravity);
			void Update(double deltaTime);
			void setLayer(int layer);
			void setFriction(float staticF, float dynamicF);
			void applyForce(exstar::Vector2d force);
			void applyForce(int x, int y);
			void applyImpulse(exstar::Vector2d impulse);
			void applyImpulse(int x, int y);
			void updateCollider();
			void toggle();
			void setState(bool enabled);
			bool getEnabled();
		private:
			
		};
	}
}
