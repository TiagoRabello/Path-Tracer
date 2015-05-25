#include "pinhole_camera.hpp"

#include <math/ray3d.hpp>
#include <math/trigonometry.hpp>
#include <math/vector3d.hpp>
#include <math/utility.hpp>

#include <cassert>

namespace cameras
{
  pinhole_camera::pinhole_camera(math::point3d  eye
                               , math::point3d  at
                               , math::vector3d up
                               , math::degrees  fovy
                               , float          nearp
                               , float          farp
                               , float          film_width
                               , float          film_height)
  : eye(eye), at(at), up(up), fovy(fovy), nearp(nearp), farp(farp)
  {
    assert(film_width >= 0.0f);
    assert(film_height >= 0.0f);

    assert(fovy.value >= 0.0f);
    assert(fovy.value <= 360.0f);

    assert(farp > nearp);

    resize(film_width, film_height);
  }

  math::ray3d pinhole_camera::generate_ray(float film_x, float film_y) const
  {
    assert(film_x >= 0.0f);
    assert(film_y >= 0.0f);
    assert(film_x <= film_width);
    assert(film_y <= film_height);

    math::ray3d ray;
    const float horizontal_rate = (film_x / film_width);
    const float vertical_rate   = (film_y / film_height);

    ray.origin = eye;

    ray.direction = math::make_vector3d(eye, near_origin)
                  + math::scaled(near_u, horizontal_rate)
                  + math::scaled(near_v, vertical_rate);

    ray.direction = math::normalized(ray.direction);

    return ray;
  }

  void pinhole_camera::resize(float film_width, float film_height)
  {
    this->film_width = film_width;
    this->film_height = film_height;

    math::vector3d z_axis = math::normalized(math::make_vector3d(at, eye));
    math::vector3d x_axis = math::normalized(math::cross(up, z_axis));
    math::vector3d y_axis = math::cross(z_axis, x_axis);

    float sz = nearp;
    float sy = sz * math::tan(fovy * 0.5f);
    float sx = sy * (film_width / film_height);
    near_origin = math::translated(eye, -math::scaled(z_axis, sz) - math::scaled(y_axis, sy) - math::scaled(x_axis, sx));

    near_u = math::scaled(x_axis, 2.0f * sx);
    near_v = math::scaled(y_axis, 2.0f * sy);
  }
}
