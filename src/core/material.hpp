#ifndef CORE_MATERIAL_HPP
#define CORE_MATERIAL_HPP

#include <graphics/color.hpp>

#include <tuple>

namespace core
{

struct material
{
  graphics::color diffuse_color;
  graphics::color specular_color;
  float specular_exponent;
};

inline bool operator==(material lhs, material rhs)
{
  return std::tie(lhs.diffuse_color, lhs.specular_color, lhs.specular_exponent)
    == std::tie(rhs.diffuse_color, rhs.specular_color, rhs.specular_exponent);
}

inline bool operator!=(material lhs, material rhs)
{
  return !(lhs == rhs);
}

}

#endif
