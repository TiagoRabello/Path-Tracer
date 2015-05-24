#ifndef LIGHTS_POINT_LIGHT_HPP
#define LIGHTS_POINT_LIGHT_HPP

#include <graphics/color.hpp>
#include <math/point3d.hpp>

namespace lights
{

struct point_light
{
  math::point3d position;
  graphics::color color;
};

}

#endif
