#ifndef Engine_H
#define Engine_H
	#include "Exstar/Utils/ArrayList.h"
	#include "Exstar/Physics/PCollision.h"
	namespace exstar{
		class Engine{
		public:
			ArrayList<exstar::Body*>* bodies = new ArrayList<exstar::Body*>();
			Engine();
			void add(exstar::Body* body);
			exstar::Body* getById(std::string id);
			void Update(double deltaTime);
			static void HandleCollision(exstar::PCollision* collision);
			static void Impulse(exstar::PCollision* collision);
			static void PositionalCorrection(exstar::PCollision* collision);
		};
	}
	#include "Exstar/Physics/Engine.cpp"
#endif