#version 440

// The transformation matrix
uniform mat4 MVP;

// Incoming position
layout (location = 0) in vec3 position_in;
layout(location = 10) in vec2 tex_coord_in;

layout (location = 0) out vec2 tex_coord;

void main()
{
	// Transform the position into screen space
	gl_Position = MVP * vec4(position_in, 1.0);

	tex_coord = tex_coord_in;
}