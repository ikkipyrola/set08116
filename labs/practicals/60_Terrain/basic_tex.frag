#version 440

uniform sampler2D tex;

layout (location = 0) in vec2 tex_coord;

layout (location = 0) out vec4 colour;

void main()
{
	colour = texture(tex, tex_coord);
	//colour = vec4(1.0, 0.0, 0.0, 1.0);
}