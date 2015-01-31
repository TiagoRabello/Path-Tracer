#ifndef _SHAPES_SPHERE_HPP
#define _SHAPES_SPHERE_HPP

#include <math/point3d.hpp>

namespace shapes
{

struct sphere
{
  math::point3d center;
  float radius;
};

inline bool operator==(sphere lhs, sphere rhs)
{
  return std::tie(lhs.center, lhs.radius) == std::tie(rhs.center, rhs.radius);
}

inline bool operator!=(sphere lhs, sphere rhs)
{
  return !(lhs == rhs);
}

}

#endif
