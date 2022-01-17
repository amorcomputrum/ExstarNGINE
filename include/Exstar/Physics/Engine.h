#pragma once

#include "Exstar/Utils/ArrayList.h"
#include "Exstar/Physics/PCollision.h"

namespace exstar{
	namespace physics{
		class Engine{
		public:
			static exstar::Vector2d GRAVITY = exstar::Vector2d(0,9.81);
			ArrayList<exstar::physics::Body*>* bodies = new ArrayList<exstar::physics::Body*>();;
			exstar::physics::PCollision collision;
			Engine();
			void add(exstar::physics::Body* body);
			exstar::physics::Body* getById(std::string id);
			void Update(double deltaTime);
			static void HandleCollision(exstar::physics::PCollision* collision);
			static void Impulse(exstar::physics::PCollision* collision);
			static void PositionalCorrection(exstar::physics::PCollision* collision);
		};
	}
}
