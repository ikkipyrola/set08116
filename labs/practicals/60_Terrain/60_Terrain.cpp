/*

TODO: Not rendering the sphere

TODO: Continue noise

*/

#include <glm/glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

mesh skybox;
effect sky_eff;
effect extra_eff;
cubemap cube_map;
vec3 fog_colour = vec3(0.5f, 0.0f, 0.2f);

// Noise texture
bool texture_not_rendered = true;
GLenum noise_texture;

//texture noise_texture;
frame_buffer perlin;
mesh example_sphere;
effect sphere_eff;
effect perlin_eff;
geometry perlin_quad;

mesh terr;
effect eff;
free_camera cam;
directional_light light;
texture tex[4];

effect glitch_eff;
frame_buffer frame;
geometry screen_quad;

const int noise_width = 512;
const int noise_height = noise_width;

// Gradient data for texture
float noise_data[noise_width * noise_height];

// Hash lookup table as defined by Ken Perlin, all numbers from 0-255 inclusive.
int static permutation[] = { 151,160,137,91,90,15,
131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,250,124,123,
5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

// Doubled to avoid overflow
int static p[512];

void Perlin()
{
	for (int i = 0; i < 512; i++)
	{
		p[i] = permutation[i%256];
	}

}

// Fade function as defined by Ken Perlin (6t^5 - 15t^4 + 10t^3)
// Smooths final output by easing coordinate values towards integral values
double fade(double t)
{
	return 6 * pow(t, 5) - 15 * pow(t, 4) + 10 * pow(t, 3);
}

// Gradient vectors
vec2 grads[] = { {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1} };

// (Same as grad in flafla code)
double dot_prod(int i, double x, double y)
{
	return grads[i][0] * x + grads[i][1] * y;
}

// fade value, dot_prod, dot_prod
double double_lerp (double t, double a, double b)
{
	return a + t * (b - a);
}

/*

void Perlin()
{
for (int i = 0; i < 512; i++)
{
p[i] = permutation[i%256];
}

}

// Fade function as defined by Ken Perlin (6t^5 - 15t^4 + 10t^3)
// Smooths final output by easing coordinate values towards integral values
double fade(double t)
{
return 6 * pow(t, 5) - 15 * pow(t, 4) + 10 * pow(t, 3);
}

// Gradient vectors
vec2 grads[] = { {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1} };

// (Same as grad in flafla code)
double dot_prod(int i, double x, double y)
{
return grads[i][0] * x + grads[i][1] * y;
}

// fade value, dot_prod, dot_prod
double double_lerp (double t, double a, double b)
{
return a + t * (b - a);
}

double generate_perlin(double x, double y)
{
// Calculate unit coordinates
int unit_x = (int)floor(x);
int unit_y = (int)floor(y);

// Location 0.0 to 1.0 within unit square
double relative_x = x - floor(x);
double relative_y = y - floor(y);

double u = fade(relative_x);
double v = fade(relative_y);

// Using unit coordinate, lookup a gradient
int oo, ol, lo, ll;
oo = p[unit_x +     p[unit_y    ]];
ol = p[unit_x +     p[unit_y + 1]];
lo = p[unit_x + 1 + p[unit_y    ]];
ll = p[unit_x + 1 + p[unit_y + 1]];

// Values to interpolate between
double lerping_xa, lerping_ya, lerping_xb, lerping_yb;
lerping_xa = dot_prod(oo, relative_x, relative_y);
lerping_xb = dot_prod(ol, relative_x - 1, relative_y);
lerping_ya = dot_prod(ll, relative_x, relative_y - 1);
lerping_yb = dot_prod(lo, relative_x - 1, relative_y - 1);

// Linear interpolation
double y1 = double_lerp(u, oo, lo),
double y2 = double_lerp(u, ol, ll);

return double_lerp(v, y1, y2);
}

*/

float generate_perlin(double x, double y)
{
	// Calculate unit coordinates
	int unit_x = (int)floor(x);
	int unit_y = (int)floor(y);

	// Location 0.0 to 1.0 within unit square
	double relative_x = x - floor(x);
	double relative_y = y - floor(y);

	// Apply fade function
	double u = fade(relative_x);
	double v = fade(relative_y);

	// Using unit coordinate, lookup a gradient
	int oo, ol, lo, ll;
	oo = p[unit_x +     p[unit_y    ]];
	ol = p[unit_x +     p[unit_y + 1]];
	lo = p[unit_x + 1 + p[unit_y    ]];
	ll = p[unit_x + 1 + p[unit_y + 1]];

	// Values to interpolate between
	double lerping_xa, lerping_ya, lerping_xb, lerping_yb;
	lerping_xa = dot_prod(oo, relative_x, relative_y);
	lerping_xb = dot_prod(ol, relative_x - 1, relative_y);
	lerping_ya = dot_prod(ll, relative_x, relative_y - 1);
	lerping_yb = dot_prod(lo, relative_x - 1, relative_y - 1);

	// Linear interpolation
	double y1 = double_lerp(u, oo, lo);
	double y2 = double_lerp(u, ol, ll);

	return (float)double_lerp(v, y1, y2);
}

/*
// initPermTexture(GLuint *texID) - create and load a 2D texture for
// a combined index permutation and gradient lookup table.
// This texture is used for 2D and 3D noise, both classic and simplex.

void initPermTexture(GLuint *texID)
{
	char *pixels;
	int i, j;

	glGenTextures(1, texID); // Generate a unique texture ID
	glBindTexture(GL_TEXTURE_2D, *texID); // Bind the texture to texture unit 0

	char *pixels = (char *)malloc(256 * 256 * 4);

	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++) 
		{
			int offset = (i * 256 + j) * 4;

			char value = perm[(j + perm[i]) & 0xFF];

			pixels[offset] = grads[value & 0x0F][0] * 64 + 64;   // Gradient x
			pixels[offset + 1] = grads[value & 0x0F][1] * 64 + 64; // Gradient y
			pixels[offset + 2] = grads[value & 0x0F][2] * 64 + 64; // Gradient z
			pixels[offset + 3] = value;                     // Permuted index
		}
	}

	// GLFW texture loading functions won't work here - we need GL_NEAREST lookup.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
*/

void generate_terrain(geometry &geom, const texture &height_map, 
	unsigned int width, unsigned int depth, float height_scale)
{
	// Contains our position, normal, tex_coordinate, texture weight and index data
	vector<vec3> positions;
	vector<vec3> normals;
	vector<vec2> tex_coords;
	vector<vec4> tex_weights;
	vector<unsigned int> indices;

	// Extract the texture data from the image
	glBindTexture(GL_TEXTURE_2D, height_map.get_id());
	auto data = new vec4[height_map.get_width() * height_map.get_height()];
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, (void *)data);

	// Determine ratio of height map to geometry
	float width_point = static_cast<float>(width) / static_cast<float>(height_map.get_width());
	float depth_point = static_cast<float>(depth) / static_cast<float>(height_map.get_height());

	// Point to work on
	vec3 point;

	// Iterate through each point, calculate vertex and add to vector
	for (int x = 0; x < height_map.get_width(); x++)
	{
		// Calculate x position of point
		point.x = -(width / 2.0f) + (width_point * static_cast<float>(x));

		for (int z = 0; z < height_map.get_height(); z++)
		{
			// Calculate z position of point
			point.z = -(depth / 2.0f) + (depth_point * static_cast<float>(z));
			// Y position based on red component of height map data
			point.y = data[(z * height_map.get_width()) + x].y * height_scale;
			// Add point to position data
			positions.push_back(point);
		}
	}

	// Add index data
	for (unsigned int x = 0; x < height_map.get_width() - 1; x++)
	{
		for (unsigned int y = 0; y < height_map.get_height() - 1; y++)
		{
			// Get four corners of patch
			unsigned int top_left = (y * height_map.get_width()) + x;
			unsigned int top_right = (y * height_map.get_width()) + x + 1;
			unsigned int bottom_left = ((y + 1) * height_map.get_width()) + x;
			unsigned int bottom_right = ((y + 1) * height_map.get_height()) + x + 1;

			// Push back indices for triangle 1 (tl,br,bl)
			indices.push_back(top_left);
			indices.push_back(bottom_right);
			indices.push_back(bottom_left);

			// Push back indices for triangle 2 (tl,tr,br)
			indices.push_back(top_left);
			indices.push_back(top_right);
			indices.push_back(bottom_right);
		}
	}

	// Resize the normals buffer
	normals.resize(positions.size());

	// Calculate normals for the height map
	for (unsigned int i = 0; i < indices.size() / 3; i++)
	{
		// Get indices for the triangle
		auto idx1 = indices[i * 3];
		auto idx2 = indices[i * 3 + 1];
		auto idx3 = indices[i * 3 + 2];

		// Calculate two sides of the triangle
		vec3 side1 = positions[idx1] - positions[idx3];
		vec3 side2 = positions[idx1] - positions[idx2];

		// Normal is normal(cross product) of these two sides
		vec3 n = normalize(cross(side2, side1));

		// Add to normals in the normal buffer using the indices for the triangle
		normals[idx1] = normals[idx1] + n;
		normals[idx2] = normals[idx2] + n;
		normals[idx3] = normals[idx3] + n;
	}

	// Normalize all the normals
	for (auto &n : normals) 
	{
		n = normalize(n);
	}

	// Add texture coordinates for geometry
	for (unsigned int x = 0; x < height_map.get_width(); x++)
	{
		for (unsigned int z = 0; z < height_map.get_height(); z++)
		{
			tex_coords.push_back(vec2(width_point * x, depth_point * z));
		}
	}

	// Calculate texture weights for each vertex
	for (unsigned int x = 0; x < height_map.get_width(); x++)
	{
		for (unsigned int z = 0; z < height_map.get_height(); z++)
		{
			// Calculate tex weight
			vec4 tex_weight(clamp(1.0f - abs(data[(height_map.get_width() * z) + x].y - 0.0f) / 0.25f, 0.0f, 1.0f),
				clamp(1.0f - abs(data[(height_map.get_width() * z) + x].y - 0.15f) / 0.25f, 0.0f, 1.0f),
				clamp(1.0f - abs(data[(height_map.get_width() * z) + x].y - 0.5f) / 0.25f, 0.0f, 1.0f),
				clamp(1.0f - abs(data[(height_map.get_width() * z) + x].y - 0.9f) / 0.25f, 0.0f, 1.0f));

			// Sum the components of the vector
			float total = tex_weight.x + tex_weight.y + tex_weight.z + tex_weight.a;
			// Divide weight by sum
			tex_weight = tex_weight / total;
			// Add tex weight to weights
			tex_weights.push_back(tex_weight);

		}
	}

	// Add necessary buffers to the geometry
	geom.add_buffer(positions, BUFFER_INDEXES::POSITION_BUFFER);
	geom.add_buffer(normals, BUFFER_INDEXES::NORMAL_BUFFER);
	geom.add_buffer(tex_coords, BUFFER_INDEXES::TEXTURE_COORDS_0);
	geom.add_buffer(tex_weights, BUFFER_INDEXES::TEXTURE_COORDS_1);
	geom.add_index_buffer(indices);

	// Delete data
	delete[] data;
}

bool load_content()
{
	// -=-=-=-=-=-=-=-=-=-=- PERLIN -=-=-=-=-=-=-=-=-=-=-=-

	// MAYBE GET RID OF ALL THIS
	perlin = frame_buffer(noise_width, noise_height);
	// Create screen quad
	vector<vec2> perl_positions{ vec2(-1.0f, -1.0f), vec2(1.0f, -1.0f), vec2(-1.0f, 1.0f), vec2(1.0f, 1.0f) };
	vector<vec2> perl_tex_coords{ vec2(0.0f, 0.0f), vec2(1.0f, 0.0f), vec2(0.0f, 1.0f), vec2(1.0f, 1.0f) };
	perlin_quad.add_buffer(perl_positions, BUFFER_INDEXES::POSITION_BUFFER);
	perlin_quad.add_buffer(perl_tex_coords, BUFFER_INDEXES::TEXTURE_COORDS_0);
	perlin_quad.set_type(GL_TRIANGLE_STRIP);
	perlin_quad.add_buffer(perl_positions, BUFFER_INDEXES::POSITION_BUFFER);
	perlin_quad.add_buffer(perl_tex_coords, BUFFER_INDEXES::TEXTURE_COORDS_0);
	perlin_eff.add_shader("C:/Users/40212722/Desktop/set08116/labs/practicals/60_Terrain/perlin.vert", GL_VERTEX_SHADER);
	perlin_eff.add_shader("C:/Users/40212722/Desktop/set08116/labs/practicals/60_Terrain/perlin.frag", GL_FRAGMENT_SHADER);
	perlin_eff.build();

	for (int i = 0; i < noise_height; i++)
	{
		for (int j = 0; j < noise_width; j++)
		{
			// HACKY WAY OF GETTING AROUND HAVING INT FOR ALL PIXELS
			// TODO: ALL NOISE DATA IS ZERO, DEBUG THIS FUCKER
			if (j >= 10 && i >= 10)
			{
				noise_data[noise_height + noise_width] = generate_perlin((double)(i / 10), (double)(j / 10));
			}
			else if (j >= 10)
			{
				noise_data[noise_height + noise_width] = generate_perlin((double)(i), (double)(j / 10));
			}
			else
			{
				noise_data[noise_height + noise_width] = generate_perlin((double)(i), (double)(j));
			}
			
		}
	}

	// -=-=-=-=-=-=-=-=-=-=- Post-processing -=-=-=-=-=-=-=-=-=-=-=-

	// Create frame buffer - use screen width and height
	frame = frame_buffer(renderer::get_screen_width(), renderer::get_screen_height());
	// Create screen quad
	vector<vec3> positions{ vec3(-1.0f, -1.0f, 0.0f), vec3(1.0f, -1.0f, 0.0f), vec3(-1.0f, 1.0f, 0.0f),
		vec3(1.0f, 1.0f, 0.0f) };
	vector<vec2> tex_coords{ vec2(0.0f, 0.0f), vec2(1.0f, 0.0f), vec2(0.0f, 1.0f), vec2(1.0f, 1.0f) };
	screen_quad.add_buffer(positions, BUFFER_INDEXES::POSITION_BUFFER);
	screen_quad.add_buffer(tex_coords, BUFFER_INDEXES::TEXTURE_COORDS_0);
	screen_quad.set_type(GL_TRIANGLE_STRIP);
	screen_quad.add_buffer(positions, BUFFER_INDEXES::POSITION_BUFFER);
	screen_quad.add_buffer(tex_coords, BUFFER_INDEXES::TEXTURE_COORDS_0);
	glitch_eff.add_shader("C:/Users/40212722/Desktop/set08116/labs/practicals/27_Texturing_Shader/simple_texture.vert", GL_VERTEX_SHADER);
	glitch_eff.add_shader("C:/Users/40212722/Desktop/set08116/labs/practicals/60_Terrain/glitch.frag", GL_FRAGMENT_SHADER);
	glitch_eff.build();

	// -=-=-=-=-=-=-=-=-=-=- Skybox -=-=-=-=-=-=-=-=-=-=-=-

	// Create box geometry for skybox
	skybox = mesh(geometry_builder::create_box(vec3(1.0f, 1.0f, 1.0f)));
	// Scale box by 100
	skybox.get_transform().scale *= 100.0f;
	// Load the cubemap
	array<string, 6> filenames = { "textures/miramar_ft.tga", "textures/miramar_bk.tga", "textures/miramar_up.tga",
		"textures/miramar_dn.tga", "textures/miramar_rt.tga", "textures/miramar_lf.tga" };
	// Create cube_map
	cube_map = cubemap(filenames);
	// Load in skybox effect
	sky_eff.add_shader("shaders/skybox.vert", GL_VERTEX_SHADER);
	sky_eff.add_shader("shaders/skybox.frag", GL_FRAGMENT_SHADER);
	// Build effect
	sky_eff.build();

	// Extra effect to handle skybox shading
	extra_eff.add_shader("C:/Users/40212722/Desktop/set08116/labs/practicals/57_Skybox/shader.vert", GL_VERTEX_SHADER);
	extra_eff.add_shader("C:/Users/40212722/Desktop/set08116/labs/practicals/57_Skybox/shader.frag", GL_FRAGMENT_SHADER);
	extra_eff.build();

	// -=-=-=-=-=-=-=-=-=-=- Perlin sphere -=-=-=-=-=-=-=-=-=-=-=-

	example_sphere = mesh(geometry_builder::create_sphere(20, 20));
	example_sphere.get_transform().scale *= 2.0f;
	example_sphere.get_transform().translate(vec3(-10.0f, 15.0f, -30.0f));

	sphere_eff.add_shader("C:/Users/40212722/Desktop/set08116/labs/practicals/60_Terrain/basic_tex.vert", GL_VERTEX_SHADER);
	sphere_eff.add_shader("C:/Users/40212722/Desktop/set08116/labs/practicals/60_Terrain/basic_tex.frag", GL_FRAGMENT_SHADER);
	sphere_eff.build();

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	
	// Geometry to load into
	geometry geom;

	// Load height map
	texture height_map("textures/height.jpg");

	// Generate terrain
	generate_terrain(geom, height_map, 20, 20, 2.0f); 

	// Use geometry to create terrain mesh
	terr = mesh(geom);

	// Load in necessary shaders
	eff.add_shader("C:/Users/40212722/Desktop/set08116/labs/practicals/60_Terrain/part_fog.frag", GL_FRAGMENT_SHADER);
	eff.add_shader("60_Terrain/terrain.vert", GL_VERTEX_SHADER);
	eff.add_shader("60_Terrain/terrain.frag", GL_FRAGMENT_SHADER);
	eff.add_shader("shaders/part_direction.frag", GL_FRAGMENT_SHADER);
	eff.add_shader("60_Terrain/part_weighted_texture_4.frag", GL_FRAGMENT_SHADER);
	// Build effect
	eff.build();

	// Material definitions
	light.set_ambient_intensity(vec4(0.3f, 0.3f, 0.3f, 1.0f));
	light.set_light_colour(vec4(0.9f, 0.9f, 0.9f, 1.0f));
	light.set_direction(normalize(vec3(1.0f, 1.0f, 1.0f)));
	terr.get_material().set_diffuse(vec4(0.5f, 0.5f, 0.5f, 1.0f));
	terr.get_material().set_specular(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	terr.get_material().set_shininess(20.0f);
	terr.get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));

	// Set the clear colour
	renderer::setClearColour(0.5f, 0.0f, 0.2f);

	// Terrian textures
	tex[0] = texture("textures/sand.jpg");
	tex[1] = texture("textures/grass.jpg");
	tex[2] = texture("textures/stone.jpg");
	tex[3] = texture("textures/snow.jpg");

	// Set camera properties
	cam.set_position(vec3(0.0f, 5.0f, 10.0f));
	cam.set_target(vec3(0.0f, 0.0f, 0.0f));
	cam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);
	glfwSetInputMode(renderer::get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return true;
}

bool update(float delta_time)
{
	// The ratio of pixels to rotation - remember the fov
	static double ratio_width = quarter_pi<float>() / static_cast<float>(renderer::get_screen_width());
	static double ratio_height =
		(quarter_pi<float>() * renderer::get_screen_aspect()) / static_cast<float>(renderer::get_screen_height());
	static double cursor_x = 0.0;
	static double cursor_y = 0.0;
	double current_x;
	double current_y;
	// Get the current cursor position
	glfwGetCursorPos(renderer::get_window(), &current_x, &current_y);
	// Calculate delta of cursor positions from last frame
	double delta_x = current_x - cursor_x;
	double delta_y = current_y - cursor_y;
	// Multiply deltas by ratios - gets actual change in orientation
	delta_x *= ratio_width;
	delta_y *= ratio_height;
	// Rotate cameras by delta
	cam.rotate(delta_x, -delta_y);
	// Use keyboard to move the camera - WASD
	vec3 translation(0.0f, 0.0f, 0.0f);
	if (glfwGetKey(renderer::get_window(), 'W'))
	{
		translation.z += 5.0f * delta_time;
	}
	if (glfwGetKey(renderer::get_window(), 'S'))
	{
		translation.z -= 5.0f * delta_time;
	}
	if (glfwGetKey(renderer::get_window(), 'A'))
	{
		translation.x -= 5.0f * delta_time;
	}
	if (glfwGetKey(renderer::get_window(), 'D'))
	{
		translation.x += 5.0f * delta_time;
	}
	// Move camera
	cam.move(translation);

	// Rotate skybox
	skybox.get_transform().rotate(vec3(0.0f, delta_time * 0.05f, 0.0f));

	// Update the camera
	cam.update(delta_time);

	// Set skybox position to camera position (camera in centre of skybox)
	skybox.get_transform().position = cam.get_position();

	// Update cursor pos
	cursor_x = current_x;
	cursor_y = current_y;
	return true;
}

bool render()
{
	auto V = cam.get_view();
	auto P = cam.get_projection();

	// -=-=-=-=-=-=-=-=-=-=- PERLIN -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	renderer::set_render_target(perlin);
	renderer::bind(perlin_eff);
	renderer::render(perlin_quad);

	// -=-=-=-=-=-=-=-=-=-=- Post-processing -=-=-=-=-=-=-=-=-=-=-=-

	// Set render target to frame buffer
	renderer::set_render_target(frame);
	// Clear frame
	renderer::clear();

	// RENDER ALL TO FRAME VVVV

	// -=-=-=-=-=-=-=-=-=-=- Skybox -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	// Disable depth test, depth mask, face culling
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);
	// Bind skybox effect
	renderer::bind(sky_eff);
	// Calculate MVP for the skybox
	auto M_sky = skybox.get_transform().get_transform_matrix();
	auto MVP_sky = P * V * M_sky;
	// Set MVP matrix uniform
	glUniformMatrix4fv(extra_eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP_sky));
	// Set cubemap uniform
	renderer::bind(cube_map, 0);
	glUniform1i(sky_eff.get_uniform_location("cubemap"), 0);
	// Render skybox
	renderer::render(skybox);
	// Enable depth test,depth mask,face culling
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_CULL_FACE);

	// -=-=-=-=-=-=-=-=-=-=- PERLIN SPHERE -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	renderer::bind(sphere_eff);
	auto MVP_sphere = P * V * example_sphere.get_transform().get_transform_matrix();
	glUniformMatrix4fv(sphere_eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP_sphere));

	if (texture_not_rendered)
	{
		glGenTextures(1, &noise_texture);
	}

	glBindTexture(GL_TEXTURE_2D, noise_texture);

	if (texture_not_rendered)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, noise_width, noise_height, 0, GL_COLOR_INDEX, GL_FLOAT, noise_data);
		texture_not_rendered = false;
	}

	glUniform1i(sphere_eff.get_uniform_location("tex"), noise_texture);

	renderer::render(example_sphere);

	// -=-=-=-=-=-=-=-=-=-=- Terrain -=-=-=-=-=-=-=-=-=-=-=-

	// Bind effect
	renderer::bind(eff);
	// Create MVP matrix
	auto M = terr.get_transform().get_transform_matrix();
	auto MVP = P * V * M;
	// Create MV matrix
	auto MV = V * M;
	// Set MVP, MV, M, N matrix uniform
	glUniformMatrix4fv(eff.get_uniform_location("MV"), 1, GL_FALSE, value_ptr(MV));
	glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));
	glUniformMatrix4fv(eff.get_uniform_location("M"), 1, GL_FALSE, value_ptr(M));
	glUniformMatrix3fv(eff.get_uniform_location("N"), 1, GL_FALSE, value_ptr(terr.get_transform().get_normal_matrix()));
	// Set eye_pos uniform to camera position
	glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(cam.get_position()));
	
	glUniform4fv(eff.get_uniform_location("fog_colour"), 1, value_ptr(vec4(fog_colour, 1.0f)));
	glUniform1f(eff.get_uniform_location("fog_start"), 100.0f);
	glUniform1f(eff.get_uniform_location("fog_end"), 200.0f);
	glUniform1f(eff.get_uniform_location("fog_density"), 0.1f);
	
	//Bind terrain material
	renderer::bind(terr.get_material(), "mat");
	// Bind Light
	renderer::bind(light, "light");
	// Bind and set texture uniforms
	renderer::bind(tex[0], 0);
	glUniform1i(eff.get_uniform_location("tex[0]"), 0);
	renderer::bind(tex[1], 1);
	glUniform1i(eff.get_uniform_location("tex[1]"), 1);
	renderer::bind(tex[2], 2);
	glUniform1i(eff.get_uniform_location("tex[2]"), 2);
	renderer::bind(tex[3], 3);
	glUniform1i(eff.get_uniform_location("tex[3]"), 3);
	
	// Render terrain
	renderer::render(terr);

	// -=-=-=-=-=-=-=-=-=-=- Post-processing -=-=-=-=-=-=-=-=-=-=-=-

	// Set render target back to the screen
	renderer::set_render_target();
	// bind the tex effect
	renderer::bind(glitch_eff);
	// MVP is now the identity matrix
	auto identity_MVP = mat4(1.0f);
	// Set MVP matrix uniform
	glUniformMatrix4fv(glitch_eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(identity_MVP));
	// Bind texture from frame buffer
	renderer::bind(frame.get_frame(), 4);
	// Set the tex uniform
	glUniform1i(glitch_eff.get_uniform_location("tex"), 4);
	// Render the screen quad
	renderer::render(screen_quad);

	// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

	return true;
}

void main()
{
	// Create application
	app application("60_Terrain");
	// Set methods
	application.set_load_content(load_content);
	application.set_update(update);
	application.set_render(render);
	// Run application
	application.run();
}