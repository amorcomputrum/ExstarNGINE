#ifndef Engine_H
#define Engine_H
	#include "Exstar/Utils/ArrayList.h"
	#include "Exstar/Physics/PCollision.h"
	namespace exstar{
		class Engine{
		public:
			ArrayList<exstar::Body>* bodies = new ArrayList<exstar::Body>;
			Engine();
			void Update(double deltaTime);
			static void Impulse(exstar::PCollision* collision);
			static void PositionalCorrection(exstar::PCollision* collision);
		};
	}
	#include "Exstar/Physics/Engine.cpp"
#endif