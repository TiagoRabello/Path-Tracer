#ifndef COLOR_HPP
#define COLOR_HPP

#include <tuple>

namespace graphics
{

struct color
{
  float red;
  float green;
  float blue;

  color& operator+=(color other)
  {
    red += other.red;
    green += other.green;
    blue += other.blue;
    return *this;
  }

  color& operator*=(color other)
  {
    red *= other.red;
    green *= other.green;
    blue *= other.blue;
    return *this;
  }

  color& operator*=(float factor)
  {
    red *= factor;
    green *= factor;
    blue *= factor;
    return *this;
  }
};

inline bool operator==(color lhs, color rhs)
{
  return std::tie(lhs.red, lhs.green, lhs.blue)
      == std::tie(rhs.red, rhs.green, rhs.blue);
}

inline bool operator!=(color lhs, color rhs)
{
  return !(lhs == rhs);
}

inline color operator+(color lhs, color rhs)
{
  return lhs += rhs;
}

inline color operator*(color lhs, color rhs)
{
  return lhs *= rhs;
}

inline color operator*(color c, float factor)
{
  return c *= factor;
}

inline color operator*(float factor, color c)
{
  return c * factor;
}

}

#endif
