#version 330 core
layout(location = 0) in vec2 Point;
uniform mat4 FirstModelMatrix;
uniform mat4 projection;
void main(){
	gl_Position = projection*(FirstModelMatrix*vec4(Point,0.0f,1.0f));
}
