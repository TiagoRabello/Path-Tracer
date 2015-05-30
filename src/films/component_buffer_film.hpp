#ifndef FILMS_COMPONENT_BUFFER_FILM
#define FILMS_COMPONENT_BUFFER_FILM

#include <graphics/color.hpp>

#include <cassert>
#include <vector>

namespace films
{

class component_buffer_film
{
  int width;
  int height;
  std::vector<float> buffer;

public:

  static const int pixel_depth = 4;

  component_buffer_film(int width, int height)
  : width( width ), height( height ), buffer( width * height * pixel_depth )
  {
    assert(width >= 0);
    assert(height >= 0);
  }

  void add_sample(int x, int y, graphics::color color)
  {
    assert(x >= 0);
    assert(y >= 0);
    assert(x < width);
    assert(y < height);

    const auto pixel_start = (x + y * width) * pixel_depth;
    buffer[pixel_start + 0] = color.red;
    buffer[pixel_start + 1] = color.green;
    buffer[pixel_start + 2] = color.blue;
    buffer[pixel_start + 3] = color.alpha;
  }

  void resize(int new_width, int new_height)
  {
    width = new_width;
    height = new_height;
    buffer.resize(width * height * pixel_depth);
  }

  int get_width() const { return width; }
  int get_height() const { return height; }

  const float *get_buffer() const { return buffer.data(); }
};

}

#endif
