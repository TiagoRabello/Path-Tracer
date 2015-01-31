#ifndef _CORE_OBJECT_HPP
#define _CORE_OBJECT_HPP

#include "material.hpp"
#include <shapes/sphere.hpp>

#include <tuple>

namespace core
{

struct object
{
  core::material material;
  shapes::sphere shape;
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

}

#endif
