#version 440

// Incoming texture containing frame information
uniform sampler2D tex;

// Incoming texture coordinate
layout(location = 0) in vec2 tex_coord;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main() 
{
	vec4 tex_colour = texture(tex, tex_coord);

	colour = vec4(1.0 - tex_colour.x, 1.0 - tex_colour.y, 1.0 - tex_colour.z, 1.0);
}