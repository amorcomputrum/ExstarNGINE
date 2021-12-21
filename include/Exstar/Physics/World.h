#ifndef World_H
#define World_H
	#include "Exstar/Physics/Body.h"
	#include "Exstar/Utils/ArrayList.h"
	namespace exstar{
		class World{
		public:
			ArrayList<exstar::Body*>* bodies;
			World();
			void Update(double deltaTime);
		};
	}
	#include "Exstar/Physics/World.cpp"
#endif