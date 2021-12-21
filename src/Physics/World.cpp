#include "Exstar/Physics/World.h"

exstar::World::World(){
	bodies = new exstar::ArrayList<exstar::Body*>();
}

void exstar::World::Update(double deltaTime){
	for(int i = 0; i < bodies->size;i++){
		bodies->get(i)->Update(deltaTime);
	}
}