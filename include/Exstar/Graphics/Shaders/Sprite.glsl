R"(

#VERTEX

#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoord;
uniform mat4 ModelMatrix;
uniform mat4 projection;
void main()
{
	gl_Position = projection*ModelMatrix*vec4(aPos,1.0f,1.0f);
	TexCoord = aTexCoord;
}

#FRAGMENT

#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;
void main()
{
	vec4 texColor = texture(ourTexture, TexCoord);
	if(texColor.a < 0.1)
		discard;
	FragColor = texColor;
}
)"