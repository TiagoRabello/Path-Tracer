#ifndef _COLOR_HPP
#define _COLOR_HPP

#include <tuple>

namespace graphics
{

struct color
{
  float red;
  float green;
  float blue;
  float alpha = 1.0f;
};

inline bool operator==(color lhs, color rhs)
{
  return std::tie(lhs.red, lhs.green, lhs.blue, lhs.alpha)
      == std::tie(rhs.red, rhs.green, rhs.blue, rhs.alpha);
}

inline bool operator!=(color lhs, color rhs)
{
  return !(lhs == rhs);
}

}

#endif
