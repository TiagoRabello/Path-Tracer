#ifndef MATH_RAY3D_HPP
#define MATH_RAY3D_HPP

#include "point3d.hpp"
#include "vector3d.hpp"

namespace math
{

struct ray3d
{
  point3d origin;
  vector3d direction;
};

}

#endif
