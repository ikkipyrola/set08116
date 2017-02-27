#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;
map<string, texture> textures;
effect eff;
effect shadow_eff;

int camChoice = 1;
free_camera freeCam;
double cursor_x = 0.0;
double cursor_y = 0.0;

target_camera targetCam;

directional_light light;
vector<point_light> points(4);
vector<spot_light> spots(5);

//shadow_map shadow;

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
	//shadow = shadow_map(renderer::get_screen_width(), renderer::get_screen_height());

	// Load geometry
	meshes["plane"] = mesh(geometry_builder::create_plane());
	meshes["plane"].get_transform().scale *= 2;
	textures["plane"] = texture("C:/Users/40212722/Desktop/set08116/labs/coursework/res/textures/jade-stone.jpg");

	meshes["box"] = mesh(geometry_builder::create_box());
	meshes["box"].get_transform().scale *= 5;
	meshes["box"].get_transform().translate(vec3(-10.0f, 2.5f, -30.0f));
	textures["box"] = texture("C:/Users/40212722/Desktop/set08116/labs/coursework/res/textures/237.jpg");

	meshes["sphere"] = mesh(geometry_builder::create_sphere(30, 30));
	meshes["sphere"].get_transform().scale *= 10;
	meshes["sphere"].get_transform().translate(vec3(10.0f, 3.0f, -20.0f));
	textures["sphere"] = texture("C:/Users/40212722/Desktop/set08116/labs/coursework/res/textures/225.jpg");

	// Set lighting values for point lights
	points[0].set_position(vec3(-25.0f, 5.0f, -15.0f));
	points[0].set_light_colour(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	points[0].set_range(30.0f);

	points[1].set_position(vec3(-25.0f, 5.0f, -35.0f));
	points[1].set_light_colour(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	points[1].set_range(20.f);

	// Set lighting values for spot lights
	spots[0].set_position(vec3(-25.0f, 10.0f, -15.0f));
	spots[0].set_light_colour(vec4(0.0f, 0.6f, 0.5f, 1.0f));
	spots[0].set_range(20.f);
	spots[0].set_direction(vec3(1.0f, -1.0f, -1.0f));
	spots[0].set_power(0.5f);

	spots[1].set_position(vec3(-25.0f, 10.0f, -35.0f));
	spots[1].set_light_colour(vec4(1.0f, 0.8f, 0.7f, 1.0f));
	spots[1].set_range(20.f);
	spots[1].set_direction(vec3(1.0f, -1.0f, 1.0f));
	spots[1].set_power(0.5f);

	spots[2].set_position(vec3(-10.0f, 10.0f, -15.0f));
	spots[2].set_light_colour(vec4(1.0f, 0.8f, 0.7f, 1.0f));
	spots[2].set_range(20.f);
	spots[2].set_direction(vec3(-1.0f, -1.0f, -1.0f));
	spots[2].set_power(0.5f);

	// Load in shaders
	eff.add_shader("shaders/basic.vert", GL_VERTEX_SHADER);
	vector<string> frag_shaders
	{ 
		"shaders/basic.frag",
		"shaders/part_point.frag", 
		"shaders/part_spot.frag", 
		"shaders/part_shadow.frag" 
	};
	eff.add_shader(frag_shaders, GL_FRAGMENT_SHADER);

	// Build effect
	eff.build();

	/*
	shadow_eff.add_shader("shaders/basic.vert", GL_VERTEX_SHADER);
	shadow_eff.add_shader("shaders/part_spot.frag", GL_FRAGMENT_SHADER); 
	
	shadow_eff.build();
	*/

	// Set free camera properties
	freeCam.set_position(vec3(0.0f, 10.0f, 10.0f));
	freeCam.set_target(meshes["box"].get_transform().position);
	freeCam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);

	// Set target camera properties
	targetCam.set_position(vec3(50.0f, 10.0f, 50.0f));
	targetCam.set_target(vec3(0.0f, 0.0f, 0.0f));
	targetCam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);

	return true;
}


bool update(float delta_time) 
{
	/* THIS IS NOT WORKING AT ALL 
	bool brighter = true;
	float range = 30.0f;
	// Change pointlight constant attenduation value
	if (brighter)
	{
		points[0].set_range(range);
		range += 2.0f;

		if (range > 50.0f)
		{
			brighter = false;
		}
	}
	else
	{
		points[0].set_range(range);
		range -= 2.0f;

		if (range < 30.0f)
		{
			brighter = true;
		}
	}
	*/

	// Update the camera
	if (camChoice == 1)
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
		freeCam.rotate(delta_x, -delta_y);

		// Use keyboard to move the camera - WSAD
		vec3 posChange;
		float movementSpeed = 0.5;
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
		freeCam.move(posChange);
		freeCam.update(delta_time);

		// Update cursor pos
		cursor_x = current_x;
		cursor_y = current_y;
	}
	else if (camChoice == 2)
	{
		targetCam.update(delta_time);
	}

	if (glfwGetKey(renderer::get_window(), GLFW_KEY_1))
	{
		camChoice = 1;
	}
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_2))
	{
		camChoice = 2;
	}

	/*
	// Update the shadow map light_position from the spot light
	shadow.light_position = spots[0].get_position();
	// do the same for light_dir property
	shadow.light_dir = spots[0].get_direction();
	*/

	return true;
}

/*
bool renderShadow()
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
		auto this_mesh = e.second;

		// Bind effect
		renderer::bind(eff);

		// Create MVP matrix
		mat4 MVP;
		mat4 M = this_mesh.get_transform().get_transform_matrix();
		auto V = shadow.get_view(); // view matrix taken from shadow map
		MVP = LightProjectionMat * V * M;

		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));

		// Render mesh
		renderer::render(this_mesh);

		return true;
	}
}

*/

bool render() 
{
	/*
	renderShadow();

	// Set render target back to the screen
	renderer::set_render_target();
	// Set face cull mode to back
	glCullFace(GL_BACK);
	*/

	for (auto &e : meshes)
	{
		// Bind shader
		renderer::bind(eff);

		auto this_mesh = e.second;

		/*
		// Create MVP matrix
		mat4 lightMVP;
		auto V = shadow.get_view(); // viewmatrix from the shadow map 
		mat4 LightProjectionMat = perspective<float>(90.f, renderer::get_screen_aspect(), 0.1f, 1000.f);
		mat4 M = this_mesh.get_transform().get_transform_matrix();

		// Multiply together with LightProjectionMat
		lightMVP = LightProjectionMat * V * M;
		*/

		mat4 M = this_mesh.get_transform().get_transform_matrix();
		mat4 MVP;
		//mat4 lightMVP;

		if (camChoice == 1)
		{
			auto V = freeCam.get_view();
			auto P = freeCam.get_projection();
			MVP = P * V * M;
			//lightMVP = P * V * M;
		}
		else if (camChoice == 2)
		{
			auto V = targetCam.get_view();
			auto P = targetCam.get_projection();
			MVP = P * V * M;
			//lightMVP = P * V * M;
		}

		/*
		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("lightMVP"), 1, GL_FALSE, value_ptr(lightMVP));
		*/

		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));

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

		// Set eye position - Get this from active camera
		if (camChoice == 1)
		{
			glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(freeCam.get_position()));
		}
		else if (camChoice == 2)
		{
			glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(targetCam.get_position()));
		}

		/*
		// Bind shadow map texture - use texture unit 1
		renderer::bind(shadow.buffer->get_depth(), 1);
		// Set the shadow_map uniform
		glUniform1i(eff.get_uniform_location("shadow_map"), 1);
		*/

		// Render geometry
		renderer::render(this_mesh);
	}

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
	application.set_render(render);

	// Run application
	application.run();
}