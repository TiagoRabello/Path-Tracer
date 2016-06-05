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

  color& operator-=(color rhs)
  {
    this->red -= rhs.red;
    this->green -= rhs.green;
    this->blue -= rhs.blue;
    return *this;
  }

  color& operator+=(color rhs)
  {
    this->red += rhs.red;
    this->green += rhs.green;
    this->blue += rhs.blue;
    return *this;
  }

  color& operator*=(color rhs)
  {
    this->red *= rhs.red;
    this->green *= rhs.green;
    this->blue *= rhs.blue;
    return *this;
  }
};

inline color operator-(color lhs, color rhs)
{
  return{ lhs.red - rhs.red, lhs.green - rhs.green, lhs.blue - rhs.blue };
}

inline color operator+(color lhs, color rhs)
{
  return{ lhs.red + rhs.red, lhs.green + rhs.green, lhs.blue + rhs.blue };
}

inline color operator*(color lhs, color rhs)
{
  return{ lhs.red * rhs.red, lhs.green * rhs.green, lhs.blue * rhs.blue };
}

inline color operator/(color lhs, float rhs)
{
  return{ lhs.red / rhs, lhs.green / rhs, lhs.blue / rhs };
}

inline bool operator==(color lhs, color rhs)
{
  return std::tie(lhs.red, lhs.green, lhs.blue)
      == std::tie(rhs.red, rhs.green, rhs.blue);
}

inline bool operator!=(color lhs, color rhs)
{
  return !(lhs == rhs);
}

}

#endif
