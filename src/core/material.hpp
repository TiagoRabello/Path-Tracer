#ifndef CORE_MATERIAL_HPP
#define CORE_MATERIAL_HPP

#include <graphics/color.hpp>
#include <math/vector3d.hpp>
#include <math/utility.hpp>

namespace core
{

struct material
{
  virtual ~material() {}

  virtual graphics::color interact(math::vector3d normal, math::vector3d in, math::vector3d out) = 0;
};

struct lambertian : material
{
  graphics::color diffuse_color;
  graphics::color specular_color;
  float specular_exponent;

  lambertian(graphics::color diffuse_color, graphics::color specular_color, float specular_exponent)
  : diffuse_color(diffuse_color)
  , specular_color(specular_color)
  , specular_exponent(specular_exponent)
  {}

  graphics::color interact(math::vector3d normal, math::vector3d in, math::vector3d out) override
  {
    // Calculate diffuse component
    auto cossine = math::dot(normal, out);
    if (cossine < 0.0f) { return{ 0.0f, 0.0f, 0.0f }; } // Light coming from behind, no transmition.

    graphics::color color = diffuse_color * cossine;

    // Calculate specular component
    const auto specular_vector = math::reflected(-in, normal);
    cossine = std::abs(math::dot(specular_vector, out));
    cossine = std::pow(cossine, specular_exponent);

    color += specular_color * cossine;

    return color;
  }
};

//struct material
//{
//  graphics::color diffuse_color;
//  graphics::color specular_color;
//  float specular_exponent;
//  float refractive_index;
//  float opacity;
//};
//
//inline bool operator==(material lhs, material rhs)
//{
//  return std::tie(lhs.diffuse_color, lhs.specular_color, lhs.specular_exponent, lhs.refractive_index)
//      == std::tie(rhs.diffuse_color, rhs.specular_color, rhs.specular_exponent, rhs.refractive_index);
//}
//
//inline bool operator!=(material lhs, material rhs)
//{
//  return !(lhs == rhs);
//}

}

#endif
