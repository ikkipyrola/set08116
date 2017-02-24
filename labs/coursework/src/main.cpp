#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;
geometry geom;
effect eff;
texture tex;

free_camera cam;
double cursor_x = 0.0;
double cursor_y = 0.0;

directional_light light;
vector<point_light> points(4);
vector<spot_light> spots(5);

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
  /*
  // Create triangle data
  vector<vec3> positions{vec3(0.0f, 1.0f, 0.0f), vec3(-1.0f, -1.0f, 0.0f), vec3(1.0f, -1.0f, 0.0f)

  };
  // Colours
  vector<vec4> colours{vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f)};

  // Add to the geometry
  geom.add_buffer(positions, BUFFER_INDEXES::POSITION_BUFFER);
  geom.add_buffer(colours, BUFFER_INDEXES::COLOUR_BUFFER);
  */
	tex = texture("C:/Users/40212722/Desktop/set08116/labs/coursework/res/textures/jade-stone.jpg");

	meshes["plane"] = mesh(geometry_builder::create_plane());
	meshes["box"] = mesh(geometry_builder::create_box());
	meshes["box"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);
	meshes["box"].get_transform().translate(vec3(-10.0f, 2.5f, -30.0f));

	// Set lighting values
	// Point 0, Position (-25, 5, -15)
	// Red, 20 range
	points[0].set_position(vec3(-25.0f, 5.0f, -15.0f));
	points[0].set_light_colour(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	points[0].set_range(20.f);
	// Point 1, Position (-25, 5, -35)
	// Red,20 range
	points[1].set_position(vec3(-25.0f, 5.0f, -35.0f));
	points[1].set_light_colour(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	points[1].set_range(20.f);
	// Point 2,Position (-10, 5, -15)
	// Red,20 range
	points[2].set_position(vec3(-10.0f, 5.0f, -15.0f));
	points[2].set_light_colour(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	points[2].set_range(20.f);
	// Point 3,Position (-10, 5, -35)
	// Red,20 range
	points[3].set_position(vec3(-10.0f, 5.0f, -35.0f));
	points[3].set_light_colour(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	points[3].set_range(20.f);
	// Spot 0, Position (-25, 10, -15)
	// Green, Direction (1, -1, -1) normalized
	// 20 range,0.5 power
	spots[0].set_position(vec3(-25.0f, 10.0f, -15.0f));
	spots[0].set_light_colour(vec4(0.0f, 1.0f, 0.0f, 1.0f));
	spots[0].set_range(20.f);
	spots[0].set_direction(vec3(1.0f, -1.0f, -1.0f));
	spots[0].set_power(0.5f);
	// Spot 1,Position (-25, 10, -35)
	// Green,Direction (1, -1, 1) normalized
	// 20 range,0.5 power
	spots[1].set_position(vec3(-25.0f, 10.0f, -35.0f));
	spots[1].set_light_colour(vec4(0.0f, 1.0f, 0.0f, 1.0f));
	spots[1].set_range(20.f);
	spots[1].set_direction(vec3(1.0f, -1.0f, 1.0f));
	spots[1].set_power(0.5f);
	// Spot 2,Position (-10, 10, -15)
	// Green,Direction (-1, -1, -1) normalized
	// 20 range,0.5 power
	spots[2].set_position(vec3(-10.0f, 10.0f, -15.0f));
	spots[2].set_light_colour(vec4(0.0f, 1.0f, 0.0f, 1.0f));
	spots[2].set_range(20.f);
	spots[2].set_direction(vec3(-1.0f, -1.0f, -1.0f));
	spots[2].set_power(0.5f);
	// Spot 3,Position (-10, 10, -35)
	// Green,Direction (-1, -1, 1) normalized
	// 20 range,0.5 power
	spots[3].set_position(vec3(-10.0f, 10.0f, -35.0f));
	spots[3].set_light_colour(vec4(0.0f, 1.0f, 0.0f, 1.0f));
	spots[3].set_range(20.f);
	spots[3].set_direction(vec3(-1.0f, -1.0f, 1.0f));
	spots[3].set_power(0.5f);
	// Spot 4,Position (-17.5, 15, -25)
	// Blue,Direction (0, -1, 0)
	// 30 range,1.0 power
	spots[4].set_position(vec3(-17.5f, 15.0f, -25.0f));
	spots[4].set_light_colour(vec4(0.0f, 0.0f, 1.0f, 1.0f));
	spots[4].set_range(20.f);
	spots[4].set_direction(vec3(0.0f, -1.0f, 0.0f));
	spots[4].set_power(0.5f);

	// Load in shaders
	eff.add_shader("shaders/basic.vert", GL_VERTEX_SHADER);
	eff.add_shader("shaders/basic.frag", GL_FRAGMENT_SHADER);
	// Build effect
	eff.build();

	// Set camera properties
	cam.set_position(vec3(0.0f, 10.0f, 10.0f));
	cam.set_target(meshes["box"].get_transform().position);
	cam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);
	return true;
}


bool update(float delta_time) 
{
	static double ratio_width = quarter_pi<float>() / static_cast<float>(renderer::get_screen_width());
	static double ratio_height =
		(quarter_pi<float>() *
		(static_cast<float>(renderer::get_screen_height()) / static_cast<float>(renderer::get_screen_width()))) /
		static_cast<float>(renderer::get_screen_height());

	double current_x;
	double current_y;
	// *********************************
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
	cam.rotate(delta_x, -delta_y);
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
	cam.move(posChange);

	// Update the camera
	cam.update(delta_time);

	// Update cursor pos
	cursor_x = current_x;
	cursor_y = current_y;

	return true;
}

bool render() 
{
	for (auto &e : meshes)
	{
		auto this_mesh = e.second;

		// Bind effect
		renderer::bind(eff);

		// Create MVP matrix
		auto M = this_mesh.get_transform().get_transform_matrix();
		auto V = cam.get_view();
		auto P = cam.get_projection();
		auto MVP = P * V * M;
		 
		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));
		
		/*
		// Set material colour - all objects red
		glUniform4fv(eff.get_uniform_location("material_colour"), 1, value_ptr(vec4(1.0f, 0.0f, 0.0f, 1.0f)));
		// Set ambient intensity - (0.3, 0.3, 0.3, 1.0)
		glUniform4fv(eff.get_uniform_location("ambient_intensity"), 1, value_ptr(vec4(0.3f, 0.3f, 0.3f, 1.0f)));
		*/

		// Bind and set texture
		renderer::bind(tex, 0);
		glUniform1i(eff.get_uniform_location("tex"), 0);

		// TRYING THESE --------------------- V

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
		glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(cam.get_position()));

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