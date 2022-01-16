#include "Exstar/exstarglad/gl.h"

#include "Exstar/Graphics/Shape.h"
#include "Exstar/Utils/Exception.h"

exstar::Shape::Shape(){}

void exstar::Shape::add(unsigned int x,unsigned int y){
	vertices->add(exstar::Point{x,y});
	if(vertices->size >= 3){
		loadShader();
	}
}

void exstar::Shape::add(exstar::Vector2d vertex){
	if(vertex.x < 0 || vertex.y < 0){
		throw exstar::exception("exstar::Shape::add - Points cannot be negative");
	}
	add(vertex.x,vertex.y);
}

void exstar::Shape::add(exstar::Point vertex){
	if(vertex.x < 0 || vertex.y < 0){
		throw exstar::exception("exstar::Shape::add - Points cannot be negative");
	}
	add(vertex.x,vertex.y);
}
void  exstar::Shape::remove(unsigned int x,unsigned int y){
	int index = getIndex(x,y);
	if(index != -1){
		remove(index);
	}
}
void  exstar::Shape::remove(exstar::Vector2d vertex){
	remove(vertex.x,vertex.y);
}
void  exstar::Shape::remove(exstar::Point vertex){
	remove(vertex.x,vertex.y);
}
void  exstar::Shape::remove(int i){
	if(vertices->size == 3){
		throw exstar::exception("exstar::Shape::remove - Cannot have less than 3 verties");
	}
	vertices->remove(i);
	loadShader();
}
exstar::Vector2d exstar::Shape::getVector(int i){
	return exstar::Vector2d(vertices->get(i).x,vertices->get(i).y);
}

exstar::Point exstar::Shape::getPoint(int i){
	return exstar::Point{vertices->get(i).x,vertices->get(i).y};
}

unsigned int exstar::Shape::getX(int i){
	return vertices->get(i).x;
}

unsigned int exstar::Shape::getY(int i){
	return vertices->get(i).y;
}

unsigned int* exstar::Shape::getVAO(){
	return &VAO;
}

int exstar::Shape::getSize(){
	return vertices->size;
}
int exstar::Shape::getIndex(unsigned int x,unsigned int y){
	for(int i = 0; i < vertices->size; i++){
		exstar::Point vertex = vertices->get(i);
		if(vertex.x == x && vertex.y == y){
			return i;
		}
	}
	return -1;
}
void exstar::Shape::loadShader(){
	if(vertices->size > 3){
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
	float vertex[vertices->size*2];
	int pos = 0;
	for(int i = 0; i < vertices->size;i++){
		vertex[pos] = vertices->get(i).x;
		pos++;
		vertex[pos] = vertices->get(i).y;
		pos++;
	}
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertex),vertex,GL_STATIC_DRAW);

	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}