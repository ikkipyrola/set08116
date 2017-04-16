#version 440

// Transformation matrices
uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 M;
uniform mat3 N;

// Incoming position, normal, texture coordinate, and texture weight
layout(location = 0) in vec3 position_in;
layout(location = 2) in vec3 normal_in;
layout(location = 10) in vec2 tex_coord_in;
layout(location = 11) in vec4 tex_weight_in;

// Outgoing vertex position, normal, texture coordinate, texture weight
// and camera space position
layout(location = 0) out vec3 position;
layout(location = 1) out vec3 normal;
layout(location = 2) out vec2 tex_coord;
layout(location = 3) out vec4 tex_weight;
layout(location = 4) out vec4 CS_position;

void main() 
{
  // Calculate screen position
  gl_Position = MVP * vec4(position_in, 1.0);

  // Calculate vertex world position
  position = (M * vec4(position_in, 1.0)).xyz;

  // Calculate camera space coordinate
  CS_position = MV * vec4(position, 1.0);

  // Transform normal
  normal = N * normal_in;

  // Pass through tex_coord and tex_weight
  tex_coord = tex_coord_in;
  tex_weight = tex_weight_in;
}