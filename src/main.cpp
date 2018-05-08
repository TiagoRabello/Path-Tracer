#include <cameras/pinhole_camera.hpp>
#include <core/scene.hpp>
#include <films/component_buffer_film.hpp>
#include <graphics/color.hpp>
#include <renderers/normal_renderer.hpp>
#include <renderers/raycaster.hpp>
#include <renderers/raytracer.hpp>

#include <GLFW/glfw3.h>

#include <algorithm>
#include <chrono>
#include <cstdlib> // For std::abort
#include <iostream>
#include <iterator>
#include <vector>

//#define CGII_SCENE

namespace
{

#ifdef CGII_SCENE
const auto screen_width = 500;
const auto screen_height = 300;
#else
const auto screen_width = 640;
const auto screen_height = 480;
#endif
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
  recursive
};

render_mode mode = render_mode::recursive;
renderers::normal_renderer render_normal;
renderers::raycaster render;
renderers::raytracer render_raytrace;

core::scene scene;
films::component_buffer_film film{ screen_width, screen_height };

#ifdef CGII_SCENE
const auto eye = math::point3d{ 0.0f, 1.0f, -1.0f };
const auto at = math::point3d{ 0.0f, 0.0f, 10.0f };
const auto up = math::vector3d{ 0.0f, 1.0f, 0.0f };
const auto fovy = math::degrees{ 60.0f };
#else
const auto eye = math::point3d{ -5.0f, 1.0f, -5.0f };
const auto at = math::point3d{ 0.0f, 1.0f, 0.0f };
const auto up = math::vector3d{ 0.0f, 1.0f, 0.0f };
const auto fovy = math::degrees{ 45.0f };
#endif
const auto nearp = 0.1f;
const auto farp = 100.0f;
const auto film_width = float(screen_width);
const auto film_height = float(screen_height);

cameras::pinhole_camera camera{ eye, at, up, fovy, nearp, farp, film_width, film_height };

void init_demo_state()
{

  //graphics::color red = { 1.0f, 0.0f, 0.0f };
  graphics::color green = { 0.0f, 1.0f, 0.0f };
  graphics::color blue = { 0.0f, 0.0f, 1.0f };

  graphics::color white = { 1.0f, 1.0f, 1.0f };
  graphics::color black = { 0.0f, 0.0f, 0.0f };

#ifdef CGII_SCENE
  graphics::color teal = { 0.0f, 0.8f, 1.0f };
  graphics::color new_blue = { 0.0f, 0.4f, 1.0f };

  // Setup demo scene
  scene.background_color.red = 0.369f;
  scene.background_color.green = 0.6f;
  scene.background_color.blue = 0.96f;

  core::object obj1;
  obj1.shape = { { -1.3f, 0.46f, 3.1f }, 1.0f };
  obj1.material = { teal, white, 5.0f, 0.0f, 0.0f };
  scene.add(obj1);

  core::object obj2;
  obj2.shape = { { 0.05f, 1.08f, 0.45f }, 0.5f };
  obj2.material = { new_blue, white, 5.0f, 0.4f, 0.0f };
  scene.add(obj2);

  lights::point_light light{ { 1.0f, 6.0f, -2.0f }, white };
  scene.add(light);
#else
  // Setup demo scene
  scene.background_color = black;

  //core::object obj1;
  //obj1.shape = { { 0.0f, 0.0f, -1.0f }, 1.0f };
  //obj1.material = { white, white, 5.0f, 1.6f };
  //scene.add(obj1);

  //core::object obj2;
  //obj2.shape = { { 0.0f, 1.75f, 0.0f }, 1.0f };
  //obj2.material = { green, white, 5.0f, 1.6f };
  //scene.add(obj2);

  //core::object obj3;
  //obj3.shape = { { 0.0f, 0.0f, 1.0f }, 1.0f };
  //obj3.material = { blue, white, 5.0f, 1.6f };
  //scene.add(obj3);

  core::object obj1;
  obj1.shape = { { 0.0f, 0.0f, -1.0f }, 1.0f };
  obj1.material = std::make_unique<core::lambertian>(white, white, 5.0f);
  scene.add(std::move(obj1));

  core::object obj2;
  obj2.shape = { { 0.0f, 1.75f, 0.0f }, 1.0f };
  obj2.material = std::make_unique<core::lambertian>(green, white, 5.0f);
  scene.add(std::move(obj2));

  core::object obj3;
  obj3.shape = { { 0.0f, 0.0f, 1.0f }, 1.0f };
  obj3.material = std::make_unique<core::lambertian>(blue, white, 5.0f);
  scene.add(std::move(obj3));

  lights::point_light light{ { -10.0f, 5.0f, 5.0f }, white };
  scene.add(light);
#endif

  // Setup OpenGL
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void framebuffer_size_callback(GLFWwindow * /*window*/, int width, int height)
{
  glViewport(0, 0, width, height);
  camera = { eye, at, up, fovy, nearp, farp, float(width), float(height) };
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
    case render_mode::recursive:
      render_raytrace(camera, scene, film);
      break;
  }

  static_assert(films::component_buffer_film::pixel_depth == 3,
                "glDrawPixels is using RGB so film must have pixel depth equal to 3.");
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
      mode = render_mode::recursive;
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