#version 440

// Model transformation matrix
uniform mat4 M;
// Transformation matrix
uniform mat4 MVP;
// Normal matrix
uniform mat3 N;

// Incoming position
layout(location = 0) in vec3 positionIn;
// Incoming normal
layout(location = 2) in vec3 normalIn;
// Incoming texture coordinate
layout(location = 10) in vec2 tex_coord_in;

// Outgoing position
layout(location = 0) out vec3 position;
// Outgoing transformed normal
layout(location = 1) out vec3 normal;
// Outgoing texture coordinate
layout(location = 2) out vec2 tex_coord;

void main() {
  // Calculate screen position
  gl_Position = MVP * vec4(positionIn, 1.0);
  // *********************************
  // Output other values to fragment shader
  position = vec3(M * vec4(positionIn, 1.0f));
  normal = N * normalIn;
  tex_coord = tex_coord_in;
  // *********************************
}