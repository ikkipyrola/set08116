#version 440

// The transformation matrix
uniform mat4 MVP;

// Incoming position
layout (location = 0) in vec3 position_in;

void main()
{
	// Transform the position into screen space
	gl_Position = MVP * vec4(position_in, 1.0);
}