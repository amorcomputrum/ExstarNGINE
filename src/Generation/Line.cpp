#include "Exstar/Generation/Line.h"
#include "Exstar/Utils/Math.h"

exstar::Line::Line(int width,int minLimitOnY,int maxLimitOnY,int minStepOnX,int maxStepOnX,int minStepOnY,int maxStepOnY,int possibilityOfStep){
	generate(width,minLimitOnY,maxLimitOnY,minStepOnX,maxStepOnX,minStepOnY,maxStepOnY,possibilityOfStep);
}

int exstar::Line::get(int i){
	return data->get(i);
}

void exstar::Line::generate(int width,int minLimitOnY,int maxLimitOnY,int minStepOnX,int maxStepOnX,int minStepOnY,int maxStepOnY,int possibilityOfStep){
	if(possibilityOfStep < 0 || possibilityOfStep > 100){
			throw std::invalid_argument("Posibility not within range 0-100");
		}
		int place = 0;
		int next = 0;
		int diff = exstar::Random(maxStepOnX,maxStepOnY);
		for(int i = 0; i<width;i++){
			if(next == 0){
				next = exstar::Random(minStepOnX,maxStepOnX);
				diff = exstar::Random(minStepOnY,maxStepOnY);
				int chance = exstar::Random(0,100);
				if(chance >= possibilityOfStep){
					if(place + diff <= maxLimitOnY){
						place += diff;
					}	
				}else{
					if(place - diff >= minLimitOnY){
						place -= diff;
					}
				}
				
			}else{
				next--;
			}
			data->add(place);
		}
}
