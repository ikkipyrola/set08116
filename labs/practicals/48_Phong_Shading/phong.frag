#version 440

// A directional light structure
struct directional_light {
  vec4 ambient_intensity;
  vec4 light_colour;
  vec3 light_dir;
};

// A material structure
struct material {
  vec4 emissive;
  vec4 diffuse_reflection;
  vec4 specular_reflection;
  float shininess;
};

// Directional light for the scene
uniform directional_light light;
// Material of the object
uniform material mat;
// Position of the camera
uniform vec3 eye_pos;
// Texture
uniform sampler2D tex;

// Incoming position
layout(location = 0) in vec3 position;
// Incoming normal
layout(location = 1) in vec3 normal;
// Incoming texture coordinate
layout(location = 2) in vec2 tex_coord;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main() {

  // *********************************
  // Calculate ambient component
  vec4 ambient_component = light.ambient_intensity * mat.diffuse_reflection;
  // Calculate diffuse component
  vec4 diffuse = max(dot(normal, light.light_dir), 0.0f) * (mat.diffuse_reflection * light.light_colour);
  // Calculate view direction
  vec3 view_dir = normalize(eye_pos - position);
  // Calculate half vector
  vec3 half_vec = normalize(light.light_dir + view_dir);
  // Calculate specular component
  vec4 specular = pow(max(dot(half_vec, normal), 0.0f), mat.shininess) * (light.light_colour * mat.specular_reflection);
  // Sample texture
  vec4 texture = texture(tex, tex_coord);
  // Calculate primary colour component
  vec4 primary = mat.emissive + ambient_component + diffuse;
  // Calculate final colour - remember alpha
  vec4 finalColour = primary * texture + specular;
  finalColour.a = 1.0f;
  colour = finalColour;
  // *********************************
}