#version 450 core

// The transformation matrix
uniform mat4 MVP;
// The model transformation matrix
uniform mat4 M;
// The normal matrix
uniform mat3 N;

// Incoming position
layout(location = 0) in vec3 positionIn;
// Incoming normal
layout(location = 2) in vec3 normalIn;
// Incoming binormal
layout(location = 3) in vec3 binormalIn;
// Incoming tangent
layout(location = 4) in vec3 tangentIn;
// Incoming texture coordinate
layout(location = 10) in vec2 tex_coord_in;

// Outgoing vertex position
layout(location = 0) out vec3 position;
// Outgoing texture coordinate
layout(location = 1) out vec2 tex_coord;
// Outgoing normal
layout(location = 2) out vec3 normal;
// Outgoing tangent
layout(location = 3) out vec3 tangent;
// Outgoing binormal
layout(location = 4) out vec3 binormal;

void main() 
{
  // Transform position into screen space
  gl_Position = MVP * vec4(positionIn, 1.0);
  // Transform position into world space
  position = (M * vec4(positionIn, 1.0)).xyz;
  // Pass through texture coordinate
  tex_coord = tex_coord_in;
  // Transform normal
  normal = N * normalIn;

  // *********************************
  // Transform tangent
  tangent = N * tangentIn;
  // Transform binormal
  binormal = N * binormalIn;
  // *********************************
}