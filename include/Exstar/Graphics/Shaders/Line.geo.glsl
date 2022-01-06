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