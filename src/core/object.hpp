#ifndef CORE_OBJECT_HPP
#define CORE_OBJECT_HPP

#include "material.hpp"

#include <math/ray3d.hpp>
#include <shapes/intersection_info.hpp>
#include <shapes/sphere.hpp>
#include <shapes/quadrilateral.hpp>

#include <boost/optional.hpp>

#include <tuple>

namespace core
{

struct object
{
  core::material material;
  shapes::quadrilateral shape;
};

inline bool operator==(object lhs, object rhs)
{
  return std::tie(lhs.material, lhs.shape)
    == std::tie(rhs.material, rhs.shape);
}

inline bool operator!=(object lhs, object rhs)
{
  return !(lhs == rhs);
}

inline bool intersects(const object& obj, math::ray3d ray)
{
  return shapes::intersects(obj.shape, ray);
}

inline boost::optional<shapes::intersection_info> closest_intersection(const object& obj, math::ray3d ray)
{
  return shapes::closest_intersection(obj.shape, ray);
}

}

#endif
