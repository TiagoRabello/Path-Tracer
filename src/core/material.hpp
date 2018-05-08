#ifndef CORE_MATERIAL_HPP
#define CORE_MATERIAL_HPP

#include <brdfs/lambertian.hpp>
#include <graphics/color.hpp>
#include <math/vector3d.hpp>
#include <math/utility.hpp>

#include <tuple>

namespace core
{

struct material
{
	brdfs::lambertian brdf;
	graphics::color emissive_color;
};

inline bool operator==(material lhs, material rhs)
{
  return std::tie(lhs.brdf, lhs.emissive_color)
      == std::tie(rhs.brdf, rhs.emissive_color);
}

inline bool operator!=(material lhs, material rhs)
{
  return !(lhs == rhs);
}

//inline graphics::color specular_reflection(material material, math::vector3d in, math::vector3d out, math::vector3d normal)
//{
//  const auto specular_vector = math::reflected(-in, normal);
//  const auto cossine = std::pow(math::dot(specular_vector, out), material.specular_exponent);
//
//  return{ 0.0f//material.specular_color.red   * cossine
//        , 0.0f//material.specular_color.green * cossine
//        , 0.0f/*material.specular_color.blue  * cossine*/ };
//}
//
//inline graphics::color diffuse_reflection(material material, math::vector3d /*in*/, math::vector3d out, math::vector3d normal)
//{
//  const auto cossine = math::dot(normal, out);
//
//  return{ material.diffuse_color.red   * cossine / math::pi
//        , material.diffuse_color.green * cossine / math::pi
//        , material.diffuse_color.blue  * cossine / math::pi };
//}

}

#endif
