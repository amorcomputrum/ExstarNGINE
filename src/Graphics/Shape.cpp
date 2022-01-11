#include "Exstar/exstarglad/gl.h"

#include "Exstar/Graphics/Shape.h"
#include "Exstar/Utils/Exception.h"

exstar::Shape::Shape(){}

void exstar::Shape::add(unsigned int x,unsigned int y){
	points->add(exstar::Point{x,y});
	if(points->size >= 3){
		loadShader();
	}
}

void exstar::Shape::add(exstar::Vector2d point){
	if(point.x < 0){
		throw exstar::exception("exstar::Shape::add - Points cannot be negative");
	}
	if(point.y < 0){
		throw exstar::exception("exstar::Shape::add - Points cannot be negative");
	}
	points->add(exstar::Point{point.x,point.y});
}

void exstar::Shape::add(exstar::Point point){
	if(point.x < 0){
		throw exstar::exception("exstar::Shape::add - Points cannot be negative");
	}
	if(point.y < 0){
		throw exstar::exception("exstar::Shape::add - Points cannot be negative");
	}
	points->add(exstar::Point{point.x,point.y});
}

exstar::Vector2d exstar::Shape::getVector(int i){
	return exstar::Vector2d(points->get(i).x,points->get(i).y);
}

exstar::Point exstar::Shape::getPoint(int i){
	return exstar::Point{points->get(i).x,points->get(i).y};
}

unsigned int exstar::Shape::getX(int i){
	return points->get(i).x;
}

unsigned int exstar::Shape::getY(int i){
	return points->get(i).y;
}

unsigned int* exstar::Shape::getVAO(){
	return &VAO;
}

int exstar::Shape::getSize(){
	return points->size;
}

void exstar::Shape::loadShader(){
	if(points->size > 3){
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
	float vertices[points->size*2];
	int pos = 0;
	for(int i = 0; i < points->size;i++){
		vertices[pos] = points->get(i).x;
		pos++;
		vertices[pos] = points->get(i).y;
		pos++;
	}
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}