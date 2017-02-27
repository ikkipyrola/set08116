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
vec4 calculate_point(in point_light point, in material mat, in vec3 position, in vec3 normal, in vec3 view_dir,
                    in vec4 tex_colour);
vec4 calculate_spot(in spot_light spot, in material mat, in vec3 position, in vec3 normal, in vec3 view_dir,
                    in vec4 tex_colour);

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

// Incoming position
layout(location = 0) in vec3 position;
// Incoming normal
layout(location = 1) in vec3 normal;
// Incoming texture coordinate
layout(location = 2) in vec2 tex_coord;
// Incoming tangent

// Outgoing colour
layout(location = 0) out vec4 colour;

void main() 
{

  colour = vec4(0.0, 0.0, 0.1, 1.0);

  // Calculate view direction
  vec3 view_dir = normalize(eye_pos - position);
  // Sample texture
  vec4 tex_col = texture(tex, tex_coord);
  // Sum point lights
  for(int i = 0; i < 3; i++)
  {
	colour += calculate_point(points[i], mat, position, normal, view_dir, tex_col);
  }
  // Sum spot lights
  for(int i = 0; i < 3; i++)
  {
	colour += calculate_spot(spots[i], mat, position, normal, view_dir, tex_col);
  }

}