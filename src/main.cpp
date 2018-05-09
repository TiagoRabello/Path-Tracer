#include <cameras/pinhole_camera.hpp>
#include <core/scene.hpp>
#include <films/component_buffer_film.hpp>
#include <graphics/color.hpp>
#include <renderers/normal_renderer.hpp>
#include <renderers/path_tracer.hpp>
#include <renderers/raycaster.hpp>

#include <GLFW/glfw3.h>

#include <algorithm>
#include <chrono>
#include <cstdlib> // For std::abort
#include <iostream>
#include <iterator>
#include <vector>

namespace
{

const auto screen_width = 400;
const auto screen_height = 400;
const auto screen_title = "path_tracer_demo";

void abort_on_error(int error_code, const char *error_description)
{
  std::cerr << "glfw error (" << error_code << "): " << error_description << std::endl;
  std::abort();
}

enum class render_mode
{
  normals_only,
  non_recursive,
  global
};

render_mode mode = render_mode::non_recursive;
renderers::normal_renderer render_normal;
renderers::raycaster render;
renderers::path_tracer render_global;

core::scene scene;
films::component_buffer_film film{ screen_width, screen_height };

const auto eye = math::point3d{ -10.0f, 1.0f, 0.0f };
const auto at = math::point3d{ 0.0f, 1.0f, 0.0f };
const auto up = math::vector3d{ 0.0f, 1.0f, 0.0f };
const auto fovy = math::degrees{ 45.0f };
const auto nearp = 0.1f;
const auto farp = 100.0f;
const auto film_width = float(screen_width);
const auto film_height = float(screen_height);

cameras::pinhole_camera camera{ eye, at, up, fovy, nearp, farp, film_width, film_height };

cameras::pinhole_camera create_cornell_box_camera(int width, int height)
{
#if 1
	const auto eye1 = math::point3d{ 278.0f, 273.0f, -800.0f };
	const auto at1 = math::point3d{ 278.0f, 273.0f, -799.0f };
#else
	const auto eye1 = math::point3d{ 278.0f, 500.0f, 3.0f };
	const auto at1 = math::point3d{ 400.0f, 0.0f, 550.0f };
#endif
	const auto up1 = math::vector3d{ 0.0f, 1.0f, 0.0f };
	const auto fovy1 = math::degrees{ 45.0f };
	const auto nearp1 = 0.035f;
	const auto farp1 = 100.0f;
	const auto film_width1 = float(width);
	const auto film_height1 = float(height);

	return { eye1, at1, up1, fovy1, nearp1, farp1, film_width1, film_height1 };
}

core::scene create_cornell_box_scene()
{
	core::scene local_scene;

	const graphics::color black = { 0.0f, 0.0f, 0.0f };
	const graphics::color red = { 0.611f, 0.0555f, 0.062f };
	const graphics::color green = { 0.117f, 0.4125f, 0.115f };
	const graphics::color blue = { 0.0f, 0.0f, 1.0f };
	const graphics::color white = { 0.7295f, 0.7355f, 0.729f };

	local_scene.background_color = black;

	core::object light;
	const auto light_albedo = graphics::color{ 0.78f, 0.78f, 0.78f };
	const auto light_intensity = graphics::color{ 4.0f * 12.0f,4.0f * 12.0f,4.0f * 12.0f };//16.86f * 4.0f, 10.76f * 4.0f, 3.7f * 4.0f * 2.0f };
	light.material = { brdfs::lambertian{ light_albedo }, light_intensity };
	light.shape = { math::point3d{ 343.0f, 546.8f, 227.0f }
	              , math::point3d{ 343.0f, 546.8f, 332.0f }
	              , math::point3d{ 213.0f, 546.8f, 332.0f }
	              , math::point3d{ 213.0f, 546.8f, 227.0f } };
	local_scene.add(light);

	core::object floor;
	floor.material = { brdfs::lambertian{ light_albedo }, black };
	floor.shape = { math::point3d{ 552.8f, 0.0f, 0.0f }
		, math::point3d{ 0.0f, 0.0f, 0.0f }
		, math::point3d{ 0.0f, 0.0f, 559.2f }
	, math::point3d{ 549.6f, 0.0f, 559.2f } };
	local_scene.add(floor);

	core::object ceiling;
	ceiling.material = { brdfs::lambertian{ white }, black };
	ceiling.shape = { math::point3d{ 556.0f, 548.9f, 0.0f }
	                , math::point3d{ 556.0f, 548.9f, 559.2f }
	                , math::point3d{ 0.0f, 548.9f, 559.2f }
	                , math::point3d{ 0.0f, 548.9f, 0.0f } };
	local_scene.add(ceiling);

	core::object back_wall;
	back_wall.material = { brdfs::lambertian{ white }, black };
	back_wall.shape = { math::point3d{ 549.6f, 0.0f, 559.2f }
	                  , math::point3d{ 0.0f, 0.0f, 559.2f }
	                  , math::point3d{ 0.0f, 548.9f, 559.2f }
	                  , math::point3d{ 556.0f, 548.9f, 559.2f } };
	local_scene.add(back_wall);

	core::object right_wall;
	right_wall.material = { brdfs::lambertian{ green }, black };
	right_wall.shape = { math::point3d{ 0.0f, 0.0f, 559.2f }
	                   , math::point3d{ 0.0f, 0.0f, 0.0f }
	                   , math::point3d{ 0.0f, 548.9f, 0.0f }
	                   , math::point3d{ 0.0f, 548.9f, 559.2f } };
	local_scene.add(right_wall);

	core::object left_wall;
	left_wall.material = { brdfs::lambertian{ red }, black };
	left_wall.shape = { math::point3d{ 552.8f, 0.0f, 0.0f }
	                  , math::point3d{ 549.6f, 0.0f, 559.2f }
	                  , math::point3d{ 556.0f, 548.9f, 559.2f }
	                  , math::point3d{ 556.0f, 548.9f, 0.0f } };
	local_scene.add(left_wall);

	core::object a_wall;
	a_wall.material = { brdfs::lambertian{ white }, black };
	a_wall.shape = { math::point3d{ 556.0f, 548.9f, 0.0f } 
										, math::point3d{ 0.0f, 548.9f, 0.0f }
	                  , math::point3d{ 0.0f, 0.0f, 0.0f }
	                  , math::point3d{ 552.8f, 0.0f, 0.0f } };
	local_scene.add(a_wall);

	 // Short Block
	{
		core::object short_block_side1;
		short_block_side1.material = { brdfs::lambertian{ white }, black };
		short_block_side1.shape = { math::point3d{ 130.0f, 165.0f, 65.0f }
		                          , math::point3d{ 82.0f, 165.0f, 225.0f }
		                          , math::point3d{ 240.0f, 165.0f, 272.0f }
		                          , math::point3d{ 290.0f, 165.0f, 114.0f } };
		local_scene.add(short_block_side1);
		
		core::object short_block_side2;
		short_block_side2.material = { brdfs::lambertian{ white }, black };
		short_block_side2.shape = { math::point3d{ 290.0f, -5.0f, 114.0f }
		                          , math::point3d{ 290.0f, 165.0f, 114.0f }
		                          , math::point3d{ 240.0f, 165.0f, 272.0f }
		                          , math::point3d{ 240.0f, -5.0f, 272.0f } };
		local_scene.add(short_block_side2);
		
		core::object short_block_side3;
		short_block_side3.material = { brdfs::lambertian{ white }, black };
		short_block_side3.shape = { math::point3d{ 130.0f, -5.0f, 65.0f }
		                          , math::point3d{ 130.0f, 165.0f, 65.0f }
		                          , math::point3d{ 290.0f, 165.0f, 114.0f }
		                          , math::point3d{ 290.0f, -5.0f, 114.0f } };
		local_scene.add(short_block_side3);
		
		core::object short_block_side4;
		short_block_side4.material = { brdfs::lambertian{ white }, black };
		short_block_side4.shape = { math::point3d{ 82.0f, -5.0f, 225.0f }
		                          , math::point3d{ 82.0f, 165.0f, 225.0f }
		                          , math::point3d{ 130.0f, 165.0f, 65.0f }
		                          , math::point3d{ 130.0f, -5.0f, 65.0f } };
		local_scene.add(short_block_side4);
		
		core::object short_block_side5;
		short_block_side5.material = { brdfs::lambertian{ white }, black };
		short_block_side5.shape = { math::point3d{ 240.0f, -5.0f, 272.0f }
		                          , math::point3d{ 240.0f, 165.0f, 272.0f }
		                          , math::point3d{ 82.0f, 165.0f, 225.0f }
		                          , math::point3d{ 82.0f, -5.0f, 225.0f } };
		local_scene.add(short_block_side5);
	}

	// Tall Block
	{
		core::object tall_block_side1;
		tall_block_side1.material = { brdfs::lambertian{ white }, black };
		tall_block_side1.shape = { math::point3d{ 423.0f, 330.0f, 247.0f }
		                         , math::point3d{ 265.0f, 330.0f, 296.0f }
		                         , math::point3d{ 314.0f, 330.0f, 456.0f }
		                         , math::point3d{ 472.0f, 330.0f, 406.0f } };
		local_scene.add(tall_block_side1);
		
		core::object tall_block_side2;
		tall_block_side2.material = { brdfs::lambertian{ white }, black };
		tall_block_side2.shape = { math::point3d{ 423.0f, -50.0f, 247.0f }
		                         , math::point3d{ 423.0f, 330.0f, 247.0f }
		                         , math::point3d{ 472.0f, 330.0f, 406.0f }
		                         , math::point3d{ 472.0f, -50.0f, 406.0f } };
		local_scene.add(tall_block_side2);
		
		core::object tall_block_side3;
		tall_block_side3.material = { brdfs::lambertian{ white }, black };
		tall_block_side3.shape = { math::point3d{ 472.0f, -50.0f, 406.0f }
		                         , math::point3d{ 472.0f, 330.0f, 406.0f }
		                         , math::point3d{ 314.0f, 330.0f, 456.0f }
		                         , math::point3d{ 314.0f, -50.0f, 456.0f } };
		local_scene.add(tall_block_side3);
		
		core::object tall_block_side4;
		tall_block_side4.material = { brdfs::lambertian{ white }, black };
		tall_block_side4.shape = { math::point3d{ 314.0f, -50.0f, 456.0f }
		                         , math::point3d{ 314.0f, 330.0f, 456.0f }
		                         , math::point3d{ 265.0f, 330.0f, 296.0f }
		                         , math::point3d{ 265.0f, -50.0f, 296.0f } };
		local_scene.add(tall_block_side4);
		
		core::object tall_block_side5;
		tall_block_side5.material = { brdfs::lambertian{ white }, black };
		tall_block_side5.shape = { math::point3d{ 265.0f, -50.0f, 296.0f }
		                         , math::point3d{ 265.0f, 330.0f, 296.0f }
		                         , math::point3d{ 423.0f, 330.0f, 247.0f }
		                         , math::point3d{ 423.0f, -50.0f, 247.0f } };
		local_scene.add(tall_block_side5);
	}

	return local_scene;
}

void init_demo_state()
{
 // // Setup demo scene
 // scene.background_color = { 0.5f, 0.5f, 0.5f };

	//const graphics::color black = { 0.0f, 0.0f, 0.0f };
	//const graphics::color red   = { 1.0f, 0.0f, 0.0f };
 // const graphics::color green = { 0.0f, 1.0f, 0.0f };
 // const graphics::color blue  = { 0.0f, 0.0f, 1.0f };
 // const graphics::color white = { 1.0f, 1.0f, 1.0f };

 // core::object obj1;
 // //obj1.shape = { { 0.0f, 0.0f, -1.5f }, 1.0f };
 // /obj1.shape = { { 0.0f, 1.0f, 3.0f }, { 0.0f, 0.0f, -1.0f } };
 // obj1.material = { red, black, 5 };
 // scene.add(obj1);

 // core::object obj2;
 // //obj2.shape = { { 0.0f, 1.5f, 0.0f }, 1.0f };
 // obj2.shape = { { 3.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } };
 // obj2.material = { green, black, 5 };
 // scene.add(obj2);

 // core::object obj3;
 // //obj3.shape = { { 0.0f, 0.0f, 1.5f }, 1.0f };
 // obj3.shape = { { 0.0f, 4.0f, 0.0f },{ 0.0f, -1.0f, 0.0f } };
 // obj3.material = { blue, black, 5 };
 // scene.add(obj3);

 // core::object obj4;
 // //obj4.shape = { { 1.0f, 0.0f, 0.0f }, 1.0f };
 // obj4.shape = { { 0.0f, -2.0f, 0.0f },{ 0.0f, 1.0f, 0.0f } };
 // obj4.material = { black, white, 5 };
 // scene.add(obj4);

 // core::object obj5;
 // //obj4.shape = { { 1.0f, 0.0f, 0.0f }, 1.0f };
 // obj5.shape = { { 0.0f, 1.0f, -3.0f },{ 0.0f, 0.0f, 1.0f } };
 // obj5.material = { white, black, 5 };
 // scene.add(obj5);

 // //lights::point_light light{ { -2.0f, 5.0f, 5.0f }, white };
 // //scene.add(light);

 // lights::point_light light{ { -1.0f, 0.0f, 0.0f }, white };
 // scene.add(light);

	scene = create_cornell_box_scene();
	camera = create_cornell_box_camera(screen_width, screen_height);

  // Setup OpenGL
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void framebuffer_size_callback(GLFWwindow * /*window*/, int width, int height)
{
  glViewport(0, 0, width, height);
  camera = create_cornell_box_camera(width, height);
  film.resize(width, height);
}

void render_frame()
{
  switch (mode)
  {
    case render_mode::normals_only:
      render_normal(camera, scene, film);
      break;
    case render_mode::non_recursive:
      render(camera, scene, film);
      break;
    case render_mode::global:
      render_global(camera, scene, film);
      break;
  }

  static_assert(films::component_buffer_film::pixel_depth == 3,
                "glDrawPixels is using RGBA so film must have pixel depth equal to 3.");
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(film.get_width(), film.get_height(), GL_RGB, GL_FLOAT, film.get_buffer());
}

void keyboard_cb(GLFWwindow *, int key, int, int action, int)
{
  if (action != GLFW_RELEASE) { return; }

  switch (key)
  {
    case GLFW_KEY_1:
    case GLFW_KEY_KP_1:
      mode = render_mode::normals_only;
      break;
    case GLFW_KEY_2:
    case GLFW_KEY_KP_2:
      mode = render_mode::non_recursive;
      break;
    case GLFW_KEY_3:
    case GLFW_KEY_KP_3:
      mode = render_mode::global;
      break;
    default:
      break;
  }
}

}

int main()
{
  glfwSetErrorCallback(abort_on_error);
  if (glfwInit() == GL_FALSE) { return -1; }

  auto window = glfwCreateWindow(screen_width, screen_height, screen_title, nullptr, nullptr);
  if (window == nullptr)
  {
    glfwTerminate();
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, keyboard_cb);

  init_demo_state();

  auto total_elapsed = std::chrono::milliseconds{ 0 };
  auto total_iterations = 0ll;
  while (!glfwWindowShouldClose(window))
  {
    const auto start_time = std::chrono::high_resolution_clock::now();
    render_frame();
    const auto end_time = std::chrono::high_resolution_clock::now();
    const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    total_elapsed += elapsed;
    ++total_iterations;

    std::cout << "Render Time: " << elapsed.count() << "ms - Average Render Time: " << total_elapsed.count() / total_iterations << "ms\n";

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}