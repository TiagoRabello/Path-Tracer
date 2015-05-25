#ifndef CAMERAS_PINHOLE_CAMERA
#define CAMERAS_PINHOLE_CAMERA

#include <math/degrees.hpp>
#include <math/point3d.hpp>
#include <math/vector3d.hpp>

namespace math { struct ray3d; }

namespace cameras
{

class pinhole_camera
{
  math::point3d  eye;
  math::point3d  at;
  math::vector3d up;

  math::degrees fovy;

  float nearp;
  float farp;

  float film_width;
  float film_height;

  math::point3d  near_origin;
  math::vector3d near_u;
  math::vector3d near_v;

  void pinhole_camera::resize(float film_width, float film_height);

public:
  pinhole_camera(math::point3d  eye
               , math::point3d  at
               , math::vector3d up
               , math::degrees  fovy
               , float          nearp
               , float          farp
               , float          film_width
               , float          film_height);

  math::ray3d generate_ray(float film_x, float film_y) const;
};

}

#endif