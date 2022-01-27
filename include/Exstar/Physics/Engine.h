#pragma once

#include "Exstar/Utils/ArrayList.h"
#include "Exstar/Physics/PCollision.h"

namespace exstar{
	namespace physics{
		class Engine{
		public:
			static exstar::Vector2d GRAVITY;
			static bool PERFORMANCE_MODE;
			static float CORRECTION_PERCENT;
			static float CORRECTION_ALLOWANCE;
			int frameRate = 0;
			ArrayList<exstar::physics::Body*>* bodies = new ArrayList<exstar::physics::Body*>();;
			exstar::physics::PCollision collision;
			Engine(int frameRate);
			void add(exstar::physics::Body* body);
			exstar::physics::Body* getById(std::string id);
			void removeById(std::string id);
			void Update();
			void HandleCollision(exstar::physics::PCollision* collision);
			void Impulse(exstar::physics::PCollision* collision);
			void PositionalCorrection(exstar::physics::PCollision* collision);
		private:
			void checkCollision(exstar::physics::Body* current, exstar::physics::Body* looking);
		};
	}
}
