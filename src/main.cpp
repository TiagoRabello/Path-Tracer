#include <GLFW/glfw3.h>

#include <cstdlib> // For std::abort
#include <iostream>

namespace
{

const auto screen_width = 640;
const auto screen_height = 480;
const auto screen_title = "path_tracer";

void log_on_error(int error_code, const char *error_description)
{
  std::cerr << "glfw error (" << error_code << "): " << error_description << std::endl;
}

void abort_on_error(int error_code, const char *error_description)
{
  log_on_error(error_code, error_description);
  std::abort();
}

void framebuffer_size_callback(GLFWwindow * /*window*/, int width, int height)
{
  glViewport(0, 0, width, height);
}

void render_frame()
{
  int width, height;
  glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
  float ratio = width / (float)height;

  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

  glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

  glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
  glEnd();
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

  while (!glfwWindowShouldClose(window))
  {
    render_frame();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}