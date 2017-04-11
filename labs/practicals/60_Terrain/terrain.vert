#version 440

// MVP transformation matrix
uniform mat4 MVP;
// M transformation matrix
uniform mat4 M;
// N transformation matrix
uniform mat3 N;

// Incoming position
layout(location = 0) in vec3 position_in;
// Incoming normal
layout(location = 2) in vec3 normal_in;
// Incoming texture coordinate
layout(location = 10) in vec2 tex_coord_in;
// Incoming texture weight
layout(location = 11) in vec4 tex_weight_in;

// Outgoing vertex position
layout(location = 0) out vec3 position;
// Transformed normal
layout(location = 1) out vec3 normal;
// Outgoing tex_coord
layout(location = 2) out vec2 tex_coord;
// Outgoing tex_weight
layout(location = 3) out vec4 tex_weight;

void main() 
{
  // Calculate screen position
  gl_Position = MVP * vec4(position_in, 1.0);
  // Calculate vertex world position
  position = (M * vec4(position_in, 1.0)).xyz;
  // Transform normal
  normal = N * normal_in;
  // Pass through tex_coord
  tex_coord = tex_coord_in;
  // Pass through tex_weight
  tex_weight = tex_weight_in;
}