#version 440

// Forward declarations
vec4 weighted_texture(in sampler2D tex[4], in vec2 tex_coord, in vec4 weights);
float calculate_fog(in float fog_coord, in vec4 fog_colour, in float fog_start, in float fog_end, in float fog_density);

// A directional light struct
#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT
struct directional_light 
{
  vec4 ambient_intensity;
  vec4 light_colour;
  vec3 light_dir;
};
#endif

// A material struct
#ifndef MATERIAL
#define MATERIAL
struct material 
{
  vec4 emissive;
  vec4 diffuse_reflection;
  vec4 specular_reflection;
  float shininess;
};
#endif

// Directional light for the scene
uniform directional_light light;

// Material of the object
uniform material mat;

// Position of the camera
uniform vec3 eye_pos;

// Textures
uniform sampler2D tex[4];

// Fog colour, start and end position, and fog density
uniform vec4 fog_colour;
uniform float fog_start;
uniform float fog_end;
uniform float fog_density;

// Incoming vertex position, normal, texture coordinate, and texture weight
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coord;
layout(location = 3) in vec4 tex_weight;
layout(location = 4) in vec4 CS_position;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main() 
{
	colour = vec4(0.0, 0.0, 0.1, 1.0);
  
	// Calculate ambient component
	vec4 ambient = mat.diffuse_reflection * light.ambient_intensity;
	// Calculate diffuse component
	vec4 diffuse = (mat.diffuse_reflection * light.light_colour) * max(dot(normal, light.light_dir), 0);
	// Calculate view direction
	vec3 view_dir = normalize(eye_pos - position);
	// Calculate half vector
	vec3 half_vector = normalize(light.light_dir + view_dir);
	// Calculate specular component
	vec4 specular = (mat.specular_reflection * light.light_colour) * pow(max(dot(normal, half_vector), 0), mat.shininess);

	// Get tex colour
	vec4 tex_colour = weighted_texture(tex, tex_coord, tex_weight);

	// Calculate primary colour component
	vec4 primary = mat.emissive + ambient + diffuse;

	// Calculate final colour
	colour += primary * tex_colour + specular;
	colour.a = 1.0;

	// Calculate fog
	float fog_coord = abs(CS_position.z / CS_position.w);
	float fog_factor =  calculate_fog(fog_coord, fog_colour, fog_start, fog_end, fog_density);
	colour += mix(colour, fog_colour, fog_factor);
}