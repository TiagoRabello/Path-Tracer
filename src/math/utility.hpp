#ifndef MATH_UTILITY_HPP
#define MATH_UTILITY_HPP

#include "point3d.hpp"
#include "vector3d.hpp"

namespace math
{

inline vector3d make_vector3d(point3d from, point3d to)
{
  return { to.x - from.x, to.y - from.y, to.z - from.z };
}

}

#endif
