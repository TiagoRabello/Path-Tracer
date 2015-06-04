#include <cameras/pinhole_camera.hpp>
#include <core/scene.hpp>
#include <films/component_buffer_film.hpp>
#include <graphics/color.hpp>
#include <renderers/normal_renderer.hpp>
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

const auto screen_width = 640;
const auto screen_height = 480;
const auto screen_title = "path_tracer_demo";

void abort_on_error(int error_code, const char *error_description)
{
  std::cerr << "glfw error (" << error_code << "): " << error_description << std::endl;
  std::abort();
}

enum class render_mode
{
  normals_only,
  non_recursive
};

render_mode mode = render_mode::non_recursive;
renderers::normal_renderer render_normal;
renderers::raycaster render;

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

void init_demo_state()
{
  // Setup demo scene
  scene.background_color.red = 0.5f;
  scene.background_color.green = 0.5f;
  scene.background_color.blue = 0.5f;

  graphics::color red;
  red.red = 1.0f;
  red.green = 0.0f;
  red.blue = 0.0f;

  graphics::color green;
  green.red = 0.0f;
  green.green = 1.0f;
  green.blue = 0.0f;

  graphics::color blue;
  blue.red = 0.0f;
  blue.green = 0.0f;
  blue.blue = 1.0f;

  graphics::color white;
  white.red = 1.0f;
  white.green = 1.0f;
  white.blue = 1.0f;

  core::object obj1;
  obj1.shape = { { 0.0f, 0.0f, -1.0f }, 1.0f };
  obj1.material = { red, white, 5 };
  scene.add(obj1);

  core::object obj2;
  obj2.shape = { { 0.0f, 1.75f, 0.0f }, 1.0f };
  obj2.material = { green, white, 5 };
  scene.add(obj2);

  core::object obj3;
  obj3.shape = { { 0.0f, 0.0f, 1.0f }, 1.0f };
  obj3.material = { blue, white, 5 };
  scene.add(obj3);

  lights::point_light light{ { -2.0f, 5.0f, 5.0f }, white };
  scene.add(light);

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
  }

  static_assert(films::component_buffer_film::pixel_depth == 4,
                "glDrawPixels is using RGBA so film must have pixel depth equal to 4.");
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(film.get_width(), film.get_height(), GL_RGBA, GL_FLOAT, film.get_buffer());
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