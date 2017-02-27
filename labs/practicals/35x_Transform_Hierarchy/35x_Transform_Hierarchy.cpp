#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;
map<string, texture> textures;
effect eff;
mesh plane_mesh;
texture plane_tex;
target_camera cam;

bool load_content() {
  // Create plane mesh
  plane_mesh = mesh(geometry_builder::create_plane());

  // *********************************
  // Create Three Identical Box Meshes
  meshes["box1"] = mesh(geometry_builder::create_box());
  meshes["box2"] = mesh(geometry_builder::create_box());
  meshes["box3"] = mesh(geometry_builder::create_box());
  // Move Box One to (0,1,0)
  meshes["box1"].get_transform().translate(vec3(0.0f, 1.0f, 0.0f));
  // Move Box Two to (0,0,1)
	  meshes["box2"].get_transform().translate(vec3(0.0f, 0.0f, 1.0f));
  // Move Box Three to (0,1,0)
	  meshes["box3"].get_transform().translate(vec3(0.0f, 1.0f, 0.0f));
  // *********************************

  // Load texture
  plane_tex = texture("textures/snow.jpg");
  textures["box1"] = texture("textures/check_2.png");
  textures["box2"] = texture("textures/check_4.png");
  textures["box3"] = texture("textures/check_5.png");

  // Load in shaders
  eff.add_shader("C:/Users/40212722/Desktop/set08116/labs/practicals/27_Texturing_Shader/simple_texture.vert", GL_VERTEX_SHADER);
  eff.add_shader("C:/Users/40212722/Desktop/set08116/labs/practicals/27_Texturing_Shader/simple_texture.frag", GL_FRAGMENT_SHADER);
  // Build effect
  eff.build();

  // Set camera properties
  cam.set_position(vec3(8.0f, 8.0f, 8.0f));
  cam.set_target(vec3(0, 1.0f, 0));
  auto aspect = static_cast<float>(renderer::get_screen_width()) / static_cast<float>(renderer::get_screen_height());
  cam.set_projection(quarter_pi<float>(), aspect, 2.414f, 1000.0f);
  return true;
}

bool update(float delta_time) {
  // *********************************
  // rotate Box one on Y axis by delta_time
	meshes["box1"].get_transform().rotate(vec3(0.0f, delta_time, 0.0f));
  // rotate Box Two on Z axis by delta_time
	meshes["box2"].get_transform().rotate(vec3(0.0f, 0.0f, delta_time));
  // rotate Box Three on Y axis by delta_time
	meshes["box3"].get_transform().rotate(vec3(0.0f, delta_time, 0.0f));
  // *********************************
  // Update the camera
  cam.update(delta_time);
  return true;
}

bool render() {
  // Super effecient render loop, notice the things we only have to do once, rather than in a loop
  // Bind effect
  renderer::bind(eff);
  // Get PV
  const auto PV = cam.get_projection() * cam.get_view();
  // Set the texture value for the shader here
  glUniform1i(eff.get_uniform_location("tex"), 0);
  // Find the lcoation for the MVP uniform
  const auto loc = eff.get_uniform_location("MVP");

  std::array<string, 3> names = {"box1", "box2", "box3"};

  // Render meshes
  for (size_t i = 0; i < meshes.size(); i++) 
  {
    // *********************************
    // SET M to be the usual mesh  transform matrix
	  auto M = meshes[names[i]].get_transform().get_transform_matrix();
    // *********************************

    // Apply the heirarchy chain
    for (size_t j = i; j > 0; j--) 
	{
      M = meshes[names[j - 1]].get_transform().get_transform_matrix() * M;
    }

    // Set MVP matrix uniform
    glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(PV * M));
    // Bind texture to renderer
    renderer::bind(textures[names[i]], 0);
    // Render mesh
    renderer::render(meshes[names[i]]);
  }

  // Render floor
  glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(PV * plane_mesh.get_transform().get_transform_matrix()));
  // Bind floor texture
  renderer::bind(plane_tex, 0);
  // Render floor
  renderer::render(plane_mesh);
  return true;
}

void main() {
  // Create application
  app application("35_Geometry_Builder");
  // Set load content, update and render methods
  application.set_load_content(load_content);
  application.set_update(update);
  application.set_render(render);
  // Run application
  application.run();
}