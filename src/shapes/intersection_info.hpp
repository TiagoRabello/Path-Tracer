#ifndef SHAPES_INTERSECTION_INFO_HPP
#define SHAPES_INTERSECTION_INFO_HPP

#include <math/point3d.hpp>
#include <math/vector3d.hpp>

#include <tuple>

namespace shapes
{

struct intersection_info
{
  math::point3d point;
  math::vector3d normal;
};

inline bool operator==(intersection_info lhs, intersection_info rhs)
{
  return std::tie(lhs.point, lhs.normal)
      == std::tie(rhs.point, rhs.normal);
}

inline bool operator!=(intersection_info lhs, intersection_info rhs)
{
  return !(lhs == rhs);
}

}

#endif
