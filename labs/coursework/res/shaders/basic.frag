#version 440

#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT
// Directional light structure
struct directional_light 
{
  vec4 ambient_intensity;
  vec4 light_colour;
  vec3 light_dir;
};
#endif

#ifndef POINT_LIGHT
#define POINT_LIGHT
// Point light information
struct point_light 
{
  vec4 light_colour;
  vec3 position;
  float constant;
  float linear;
  float quadratic;
};
#endif

#ifndef SPOT_LIGHT
#define SPOT_LIGHT
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
#endif

#ifndef MATERIAL
#define MATERIAL
// Material data
struct material 
{
  vec4 emissive;
  vec4 diffuse_reflection;
  vec4 specular_reflection;
  float shininess;
};
#endif

// Forward declarations of used functions
vec4 calculate_point(in point_light point, in material mat, in vec3 position, in vec3 normal, in vec3 view_dir,
                    in vec4 tex_colour);
vec4 calculate_spot(in spot_light spot, in material mat, in vec3 position, in vec3 normal, in vec3 view_dir,
                    in vec4 tex_colour);
float calculate_shadow(in sampler2D shadow_map, in vec4 light_space_pos);
vec3 calc_normal(in vec3 normal, in vec3 tangent, in vec3 binormal, in sampler2D normal_map, in vec2 tex_coord);

// Point lights being used in the scene
uniform point_light points[3];
// Spot lights being used in the scene
uniform spot_light spots[3];

// Texture to sample from
uniform sampler2D tex;
// Material of the object being rendered
uniform material mat;
// Position of the eye (camera)
uniform vec3 eye_pos;
// Shadow map to sample from
uniform sampler2D shadow_map;
// Normal map to sample from
uniform sampler2D normal_map;

// Incoming position
layout(location = 0) in vec3 position;
// Incoming normal
layout(location = 1) in vec3 normal;
// Incoming texture coordinate
layout(location = 2) in vec2 tex_coord;
// Incoming light space position
layout(location = 3) in vec4 light_space_pos;
// Incoming tangent
layout(location = 4) in vec3 tangent;
// Incoming binormal
layout(location = 5) in vec3 binormal;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main() 
{

  colour = vec4(0.0, 0.0, 0.1, 1.0);

  // Calculate shade factor
  float shade_factor = calculate_shadow(shadow_map, light_space_pos);
  // Calculate view direction
  vec3 view_dir = normalize(eye_pos - position);
  // Sample texture
  vec4 tex_col = texture(tex, tex_coord);
  // Calculate new normal for normal mapping
  vec3 normal_map_normal = calc_normal(normal, tangent, binormal, normal_map, tex_coord);
  // Sum point lights
  for(int i = 0; i < 3; i++)
  {
	colour += calculate_point(points[i], mat, position, normal_map_normal, view_dir, tex_col);
  }
  // Sum spot lights
  for(int i = 0; i < 3; i++)
  {
	colour += calculate_spot(spots[i], mat, position, normal_map_normal, view_dir, tex_col);
  }
  // Scale colour by shade
  colour *= shade_factor;
}