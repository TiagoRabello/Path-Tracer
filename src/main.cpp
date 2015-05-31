#include <cameras/pinhole_camera.hpp>
#include <core/scene.hpp>
#include <films/component_buffer_film.hpp>
#include <graphics/color.hpp>
#include <renderers/normal_renderer.hpp>

#include <GLFW/glfw3.h>

#include <algorithm>
#include <cstdlib> // For std::abort
#include <iostream>
#include <iterator>
#include <vector>

namespace
{

const auto screen_width = 640;
const auto screen_height = 480;
const auto screen_title = "path_tracer_demo";

void log_on_error(int error_code, const char *error_description)
{
  std::cerr << "glfw error (" << error_code << "): " << error_description << std::endl;
}

void abort_on_error(int error_code, const char *error_description)
{
  log_on_error(error_code, error_description);
  std::abort();
}

core::scene scene;
renderers::normal_renderer render;
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

  core::object obj1;
  obj1.shape = { { 0.0f, 0.0f, 0.0f }, 1.0f };
  obj1.material = {};
  scene.add(obj1);

  core::object obj2;
  obj2.shape = { { 0.0f, 2.0f, 0.0f }, 1.0f };
  obj2.material = {};
  scene.add(obj2);

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
  render(camera, scene, film);

  static_assert(films::component_buffer_film::pixel_depth == 4,
                "glDrawPixels is using RGBA so film must have pixel depth equal to 4.");
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(film.get_width(), film.get_height(), GL_RGBA, GL_FLOAT, film.get_buffer());
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

  init_demo_state();

  while (!glfwWindowShouldClose(window))
  {
    render_frame();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}