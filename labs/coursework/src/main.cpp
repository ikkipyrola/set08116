#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;
map<string, texture> textures; // map<string, texture*> textures;
map<string, texture> normal_maps;
effect eff;

// Meshes and textures for the transform hierarchy
map<string, mesh> transform_meshes;
map<string, texture> transform_textures;

// Cameras
int cam_choice = 1;
free_camera free_cam;
double cursor_x = 0.0;
double cursor_y = 0.0;
target_camera target_cam;

// Lights
directional_light light;
vector<point_light> points(3);
vector<spot_light> spots(3);

// Shadows
shadow_map shadow;
effect shadow_eff;

bool initialise() 
{
	// Set input mode - hide the cursor
	glfwSetInputMode(renderer::get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Capture initial mouse position
	glfwGetCursorPos(renderer::get_window(), &cursor_x, &cursor_y);

	return true;
}

bool load_content()
{
	// Create shadow map- use screen size
	shadow = shadow_map(renderer::get_screen_width(), renderer::get_screen_height());

	// Load geometry
	meshes["plane"] = mesh(geometry_builder::create_plane());
	meshes["plane"].get_transform().scale *= 2;
	textures["plane"] = texture("textures/231.jpg");
	normal_maps["plane"] = texture("textures/231_norm.jpg");
	//dissolve = texture("textures/blend_map2.jpg");

	meshes["box"] = mesh(geometry_builder::create_box(vec3(5.0f, 5.0f, 5.0f)));
	meshes["box"].get_transform().translate(vec3(-15.0f, 2.5f, -40.0f));
	textures["box"] = texture("textures/237.jpg");
	normal_maps["box"] = texture("textures/237_norm.jpg");

	material mat;
	mat.set_emissive(vec4(0.2f, 0.2f, 0.2f, 1.0f));
	mat.set_specular(vec4(0.8f, 0.8f, 1.0f, 1.0f));
	mat.set_shininess(20.0f);
	meshes["box"].set_material(mat);

	meshes["sphere"] = mesh(geometry_builder::create_sphere(50, 50));
	meshes["sphere"].get_transform().scale *= 10;
	meshes["sphere"].get_transform().translate(vec3(10.0f, 3.0f, -20.0f));
	textures["sphere"] = texture("textures/225.jpg");
	normal_maps["sphere"] = texture("textures/225_norm.jpg");

	mat.set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	mat.set_specular(vec4(0.5f, 0.0f, 0.5f, 1.0f));
	mat.set_shininess(40.0f);
	mat.set_diffuse(vec4(0.2f, 0.0f, 0.2f, 1.0f));
	meshes["sphere"].set_material(mat);

	// Set lighting values for point lights
	points[0].set_position(vec3(-25.0f, 20.0f, -15.0f));
	points[0].set_light_colour(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	points[0].set_range(30.0f);

	points[1].set_position(vec3(-25.0f, 5.0f, -10.0f));
	points[1].set_light_colour(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	points[1].set_range(20.f);

	// General light
	points[2].set_position(vec3(-10.0f, 30.0f, -15.0f));
	points[2].set_light_colour(vec4(1.0f, 0.9f, 0.9f, 1.0f));
	points[2].set_range(50.f);

	// Set lighting values for spot lights
	spots[0].set_position(vec3(-25.0f, 20.0f, -15.0f));
	spots[0].set_light_colour(vec4(1.0f, 0.8f, 0.7f, 1.0f));
	spots[0].set_range(20.f);
	spots[0].set_direction(normalize(vec3(1.0f, -1.0f, -1.0f)));
	spots[0].set_power(0.5f);

	spots[1].set_position(vec3(-25.0f, 20.0f, -35.0f));
	spots[1].set_light_colour(vec4(0.0f, 0.6f, 0.5f, 1.0f));
	spots[1].set_range(20.f);
	spots[1].set_direction(vec3(1.0f, -1.0f, 1.0f));
	spots[1].set_power(0.5f);

	spots[2].set_position(vec3(-10.0f, 20.0f, -15.0f));
	spots[2].set_light_colour(vec4(1.0f, 0.8f, 0.7f, 1.0f));
	spots[2].set_range(20.f);
	spots[2].set_direction(vec3(-1.0f, -1.0f, -1.0f));
	spots[2].set_power(0.5f);

	/*
	// Create transform meshes
	material sphere_mat;
	sphere_mat.set_diffuse(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	transform_meshes["sphere_1"] = mesh(geometry_builder::create_sphere(50, 50));
	transform_meshes["sphere_1"].set_material(sphere_mat);
	transform_meshes["sphere_2"] = mesh(geometry_builder::create_sphere(50, 50));
	transform_meshes["sphere_1"].set_material(sphere_mat);
	transform_meshes["sphere_3"] = mesh(geometry_builder::create_sphere(50, 50));
	transform_meshes["sphere_1"].set_material(sphere_mat);

	transform_meshes["sphere_1"].get_transform().translate(vec3(0.0f, 2.0f, 0.0f));
	transform_meshes["sphere_2"].get_transform().translate(vec3(0.0f, 0.0f, 2.0f));
	transform_meshes["sphere_3"].get_transform().translate(vec3(0.0f, 2.0f, 0.0f));

	transform_textures["sphere_1"] = texture("textures/jade-stone.jpg");
	transform_textures["sphere_2"] = texture("textures/stones.jpg");
	transform_textures["sphere_3"] = texture("textures/jade-stone.jpg");
	*/

	meshes["sphere_1"] = mesh(geometry_builder::create_sphere(50, 50));
	meshes["sphere_2"] = mesh(geometry_builder::create_sphere(50, 50));
	meshes["sphere_3"] = mesh(geometry_builder::create_sphere(50, 50));

	meshes["sphere_1"].get_transform().translate(vec3(-10.0f, 25.0f, -15.0f));
	meshes["sphere_2"].get_transform().translate(vec3(-10.0f, 20.0f, -14.0f));
	meshes["sphere_3"].get_transform().translate(vec3(-10.0f, 0.0f, 0.0f));

	textures["sphere_1"] = texture("textures/jade-stone.jpg");
	textures["sphere_2"] = texture("textures/stones.jpg");
	textures["sphere_3"] = texture("textures/jade-stone.jpg");

	// Load in shaders
	eff.add_shader("shaders/basic.vert", GL_VERTEX_SHADER);
	vector<string> frag_shaders
	{ 
		"shaders/basic.frag",
		"shaders/part_point.frag", 
		"shaders/part_spot.frag", 
		"shaders/part_shadow.frag",
		//"shaders/part_normal_map.frag",
		//"shaders/part_direction.frag"
	};
	eff.add_shader(frag_shaders, GL_FRAGMENT_SHADER);

	shadow_eff.add_shader("shaders/basic.vert", GL_VERTEX_SHADER);
	shadow_eff.add_shader(frag_shaders, GL_FRAGMENT_SHADER);
	 
	// Build effects
	eff.build();
	shadow_eff.build();

	// Set free camera properties
	free_cam.set_position(vec3(0.0f, 10.0f, 10.0f));
	free_cam.set_target(meshes["box"].get_transform().position);
	free_cam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);

	// Set target camera properties
	target_cam.set_position(vec3(-100.0f, 10.0f, -10.0f));
	target_cam.set_target(meshes["sphere"].get_transform().position + vec3(0.0f, 30.0f, 0.0f));
	target_cam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);

	return true;
}


bool update(float delta_time) 
{
	// Rotate the transform hierarchy spheres
	meshes["sphere_1"].get_transform().rotate(vec3(0.0f, delta_time, 0.0f));
	meshes["sphere_2"].get_transform().rotate(vec3(0.0f, 0.0f, delta_time));
	meshes["sphere_3"].get_transform().rotate(vec3(0.0f, delta_time, 0.0f));

	// Update the camera
	if (cam_choice == 1)
	{
		static double ratio_width = quarter_pi<float>() / static_cast<float>(renderer::get_screen_width());
		static double ratio_height =
			(quarter_pi<float>() *
			(static_cast<float>(renderer::get_screen_height()) / static_cast<float>(renderer::get_screen_width()))) /
			static_cast<float>(renderer::get_screen_height());

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
		// delta_y - x-axis rotation
		// delta_x - y-axis rotation
		free_cam.rotate(delta_x, -delta_y);

		// Use keyboard to move the camera - WSAD
		vec3 posChange;
		float movementSpeed = 1.0f;
		if (glfwGetKey(renderer::get_window(), GLFW_KEY_W))
		{
			posChange = vec3(0.0f, 0.0f, movementSpeed);
		}
		if (glfwGetKey(renderer::get_window(), GLFW_KEY_S))
		{
			posChange = vec3(0.0f, 0.0f, -movementSpeed);
		}
		if (glfwGetKey(renderer::get_window(), GLFW_KEY_A))
		{
			posChange = vec3(-movementSpeed, 0.0f, 0.0f);
		}
		if (glfwGetKey(renderer::get_window(), GLFW_KEY_D))
		{
			posChange = vec3(movementSpeed, 0.0f, 0.0f);
		}

		// Move camera
		free_cam.move(posChange);
		free_cam.update(delta_time);

		// Update cursor pos 
		cursor_x = current_x;
		cursor_y = current_y;
	}
	else if (cam_choice == 2)
	{
		target_cam.update(delta_time);
	}

	if (glfwGetKey(renderer::get_window(), GLFW_KEY_1))
	{
		cam_choice = 1;
	}
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_2))
	{
		cam_choice = 2;
	}

	// Update the shadow map light_position from the spot light
	shadow.light_position = spots[0].get_position();
	// do the same for light_dir property
	shadow.light_dir = spots[0].get_direction();

	return true;
}

bool render_shadow_map()
{
	// Set render target to shadow map
	renderer::set_render_target(shadow);
	// Clear depth buffer bit
	glClear(GL_DEPTH_BUFFER_BIT);
	// Set face cull mode to front
	glCullFace(GL_FRONT);

	mat4 LightProjectionMat = perspective<float>(90.f, renderer::get_screen_aspect(), 0.1f, 1000.f);

	// Bind shader
	renderer::bind(shadow_eff);

	for (auto &e : meshes)
	{
		if ((e.first).compare("plane"))
		{
			auto this_mesh = e.second;

			// Create MVP matrix (view matrix from shadow map)
			mat4 MVP;
			mat4 M = this_mesh.get_transform().get_transform_matrix();
			auto V = shadow.get_view();
			MVP = LightProjectionMat * V * M;

			// Set MVP matrix uniform
			glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));

			// Render mesh
			renderer::render(this_mesh);

			return true;
		}
	}
}

bool render() 
{

	// Set render target back to the screen
	renderer::set_render_target();
	// Set face cull mode to back
	glCullFace(GL_BACK);

	// Bind shader
	renderer::bind(eff);

	mat4 MVP;
	mat4 PV;
	mat4 M;

	for (auto &e : meshes)
	{
		auto this_mesh = e.second;

		if (cam_choice == 1)
		{
			PV = free_cam.get_projection() * free_cam.get_view();

		}
		else if (cam_choice == 2)
		{
			PV = target_cam.get_projection() * target_cam.get_view();
		}
		
		// Create MVP matrix
		M = this_mesh.get_transform().get_transform_matrix();

		if (e.first == "sphere_2")
		{
			M = meshes["sphere_1"].get_transform().get_transform_matrix() * 
				meshes["sphere_2"].get_transform().get_transform_matrix();
		}
		else if (e.first == "sphere_3")
		{
			M = meshes["sphere_1"].get_transform().get_transform_matrix() *
				meshes["sphere_2"].get_transform().get_transform_matrix() *
				meshes["sphere_3"].get_transform().get_transform_matrix();
		}

		MVP = PV * M;

		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));

		// Create lightMVP uniform
		mat4 lightMVP;
		auto lV = shadow.get_view();
		mat4 LightProjectionMat = perspective<float>(90.f, renderer::get_screen_aspect(), 0.1f, 1000.f);
		// Multiply together with LightProjectionMat
		lightMVP = LightProjectionMat * lV * M;
		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("lightMVP"), 1, GL_FALSE, value_ptr(lightMVP));

		// Bind and set textures
		renderer::bind(textures[e.first], 0);
		glUniform1i(eff.get_uniform_location("tex"), 0);

		// Set M matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("M"), 1, GL_FALSE, value_ptr(M));
		// Set N matrix uniform - remember - 3x3 matrix
		glUniformMatrix3fv(eff.get_uniform_location("N"), 1, GL_FALSE, value_ptr(this_mesh.get_transform().get_normal_matrix()));
		// Bind material
		renderer::bind(this_mesh.get_material(), "mat");
		// Bind point lights
		renderer::bind(points, "points");
		// Bind spot lights
		renderer::bind(spots, "spots");

		/*
		// Bind light
		renderer::bind(light, "light");
		*/

		/*
		// Bind normal_map
		renderer::bind(normalMaps[e.first], 1);
		// Set normal_map uniform
		glUniform1i(eff.get_uniform_location("normalMap"), 1);
		*/

		// Set eye position - Get this from active camera
		if (cam_choice == 1)
		{
			glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(free_cam.get_position()));
		}
		else if (cam_choice == 2)
		{
			glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(target_cam.get_position()));
		}

		// Bind shadow map texture - use texture unit 1
		renderer::bind(shadow.buffer->get_depth(), 1);
		// Set the shadow_map uniform
		glUniform1i(eff.get_uniform_location("shadow_map"), 1);

		// Render geometry
		renderer::render(this_mesh);
	}

	return true;
}

bool ren()
{
	render_shadow_map();
	render();
	
	return true;
}

void main() 
{
	// Create application
	app application("Graphics Coursework");

	// Set load content, update and render methods
	application.set_load_content(load_content);
	application.set_initialise(initialise);
	application.set_update(update);
	application.set_render(ren);

	// Run application
	application.run();
}