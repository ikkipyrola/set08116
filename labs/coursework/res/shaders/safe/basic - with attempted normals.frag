#version 440

// Directional light structure
struct directional_light 
{
  vec4 ambient_intensity;
  vec4 light_colour;
  vec3 light_dir;
};

// Point light information
struct point_light 
{
  vec4 light_colour;
  vec3 position;
  float constant;
  float linear;
  float quadratic;
};

// Spot light data
struct spot_light 
{
  vec4 light_colour;
  vec3 position;
  vec3 direction;
  float constant;
  float linear;
  float quadratic;
  float power;
};

// Material data
struct material 
{
  vec4 emissive;
  vec4 diffuse_reflection;
  vec4 specular_reflection;
  float shininess;
};

// Forward declarations of used functions
vec4 calculate_direction(in directional_light light, in material mat, in vec3 normal, in vec3 view_dir,
                    in vec4 tex_colour);
vec4 calculate_point(in point_light point, in material mat, in vec3 position, in vec3 normal, in vec3 view_dir,
                    in vec4 tex_colour);
vec4 calculate_spot(in spot_light spot, in material mat, in vec3 position, in vec3 normal, in vec3 view_dir,
                    in vec4 tex_colour);
vec3 calc_normal(in vec3 normal, in vec3 tangent, in vec3 binormal, in sampler2D normal_map, in vec2 tex_coord);

// Point lights being used in the scene
uniform point_light points[2];
// Spot lights being used in the scene
uniform spot_light spots[3];
// Direction light being used in the scene
uniform directional_light light;

// Texture to sample from
uniform sampler2D tex;
// Material of the object being rendered
uniform material mat;
// Position of the eye (camera)
uniform vec3 eye_pos;
// Normal map to sample from
uniform sampler2D normalMap;

// Incoming position
layout(location = 0) in vec3 position;
// Incoming normal
layout(location = 1) in vec3 normal;
// Incoming texture coordinate
layout(location = 2) in vec2 tex_coord;
// Incoming tangent
layout(location = 3) in vec3 tangent;
// Incoming binormal
layout(location = 4) in vec3 binormal;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main() {

  colour = vec4(0.0, 0.0, 0.1, 1.0);

  // Calculate view direction
  vec3 view_dir = normalize(eye_pos - position);
  // Sample texture
  vec4 tex_col = texture(tex, tex_coord);
  // Sum point lights
  for(int i = 0; i < 2; i++)
  {
	colour += calculate_point(points[i], mat, position, normal, view_dir, tex_col);
  }
  // Sum spot lights
  for(int i = 0; i < 3; i++)
  {
	colour += calculate_spot(spots[i], mat, position, normal, view_dir, tex_col);
  }
  // Calculate normal from normal map
  vec3 finalNormal = calc_normal(normal, tangent, binormal, normalMap, tex_coord);
  colour += calculate_direction(light, mat, finalNormal, view_dir, tex_col);

}