#version 430 core

// Incoming texture containing frame information
uniform sampler2D tex;

// Incoming texture coordinate
layout(location = 0) in vec2 tex_coord;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main() 
{
	vec4 tex_colour = texture(tex, tex_coord);

	if(tex_colour.x > 0.8)
	{
		tex_colour *= 1.5;
	}
	
	if(tex_colour.y > 0.8)
	{
		tex_colour *= 0.5;
	}

	colour = tex_colour;
}