R"(

#VERTEX

#version 330 core
layout (location = 0) in vec2 position;
uniform mat4 ModelMatrix;
uniform mat4 projection;
void main()
{
	gl_Position = projection*(ModelMatrix*vec4(position,1.0f));
}

#FRAGMENT

#version 330 core
uniform vec4 Color;
void main()
{
	gl_FragColor = Color;
}
)"