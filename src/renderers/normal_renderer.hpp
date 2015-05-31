#ifndef RENDERERS_NORMAL_RENDERER
#define RENDERERS_NORMAL_RENDERER

#include <core/intersection_info.hpp>
#include <graphics/color.hpp>

#include <utility>

namespace renderers
{

struct normal_renderer
{
  graphics::color shade(const core::intersection_info& info) const
  {
    graphics::color color;
    auto normal = info.shape_info.normal;

    color.red = (normal.x + 1.0f) / 2.0f;
    color.green = (normal.y + 1.0f) / 2.0f;
    color.blue = (normal.z + 1.0f) / 2.0f;

    return color;
  }

  template<typename CameraType, typename SceneType, typename FilmType>
  FilmType&& operator()(CameraType&& camera, SceneType&& scene, FilmType&& film) const
  {
    const auto width = camera.get_width();
    const auto height = camera.get_height();

    for (int y = 0; y < height; ++y)
    {
      for (int x = 0; x < width; ++x)
      {
        const auto ray = camera.generate_ray(float(x), float(y));
        const auto closest_inter = closest_intersection(scene, ray);

        graphics::color color;
        if (closest_inter.is_initialized())
        {
          color = shade(closest_inter.get());
        }
        else
        {
          color = scene.background_color;
        }

        film.add_sample(x, y, color);
      }
    }

    return std::forward<FilmType>(film);
  }
};

}

#endif
