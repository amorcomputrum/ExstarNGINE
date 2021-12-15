#include "Exstar/Utils/Exception.h"
#include "Exstar/Utils/Color.h"
const exstar::Color exstar::Color::Black(0,0,0);
const exstar::Color exstar::Color::Red(255,0,0);
const exstar::Color exstar::Color::Green(0,255,0);
const exstar::Color exstar::Color::Blue(0,0,255);
const exstar::Color exstar::Color::White(255,255,255);
exstar::Color::Color(int r,int g,int b){
	if((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255)){
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 255;
	}else{
		throw exstar::exception("exstar::Color::Color - Out of Range 0-255");
	}
}
exstar::Color::Color(int r,int g,int b,int a){
	if((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255) && (a >= 0 && a <= 255)){
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}else{
		throw exstar::exception("exstar::Color::Color - Out of Range 0-255");
	}
}