#ifndef CORE_MATERIAL_HPP
#define CORE_MATERIAL_HPP

#include <graphics/color.hpp>
#include <math/vector3d.hpp>
#include <math/utility.hpp>

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

inline graphics::color specular_reflection(material material, math::vector3d in, math::vector3d out, math::vector3d normal)
{
  const auto specular_vector = math::reflected(-in, normal);
  const auto cossine = std::pow(math::dot(specular_vector, out), material.specular_exponent);

  return{ material.specular_color.red   * cossine
        , material.specular_color.green * cossine
        , material.specular_color.blue  * cossine };
}

inline graphics::color diffuse_reflection(material material, math::vector3d /*in*/, math::vector3d out, math::vector3d normal)
{
  const auto cossine = math::dot(normal, out);

  return{ material.diffuse_color.red   * cossine
        , material.diffuse_color.green * cossine
        , material.diffuse_color.blue  * cossine };
}

}

#endif
