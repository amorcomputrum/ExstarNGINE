R"(

#VERTEX

#version 330 core
layout(location = 0) in vec2 Point;
uniform mat4 FirstModelMatrix;
uniform mat4 projection;
void main(){
	gl_Position = projection*(FirstModelMatrix*vec4(Point,0.0f,1.0f));
}

#FRAGMENT

#version 330 core
uniform vec4 Color;
void main()
{
	gl_FragColor = Color;
}

#GEOMETRY

#version 330 core
layout (points) in;
layout (line_strip, max_verticies = 2) out;
uniform vec2 Offset;
void main(){
	gl_Postition = gl_in[0].gl_Position;
	EmitVertex();

	gl_Position = gl_in[0].glPosition + vec4(Offset,0.0f,1.0f);
	EmitVertex();

	EndPrimitive();
}
)"