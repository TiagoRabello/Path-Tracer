#ifndef RENDERERS_RAYTRACER
#define RENDERERS_RAYTRACER

#include <core/intersection_info.hpp>
#include <graphics/color.hpp>
#include <math/ray3d.hpp>
#include <math/vector3d.hpp>
#include <math/utility.hpp>

#include <utility>

namespace renderers
{

struct raytracer
{
  int max_depth = 5;

  template<typename SceneType>
  graphics::color shade_direct_lighting(SceneType&& scene, math::ray3d ray, const core::intersection_info& info) const
  {
    graphics::color color;
    color.red = 0.0f;
    color.green = 0.0f;
    color.blue = 0.0f;

    const auto is_back_side = (0.0f < math::dot(ray.direction, info.shape_info.normal));
    const auto normal = (is_back_side ? -info.shape_info.normal : info.shape_info.normal);

    for (auto& light : scene.get_lights())
    {
      auto light_vector = math::make_vector3d(info.shape_info.point, light.position);
      auto light_distance = math::length(light_vector);
      light_vector = math::scaled(light_vector, 1 / light_distance);

      // Move intersection point forward a little bit to avoid self-intersections.
      auto point = math::translated(info.shape_info.point, math::scaled(light_vector, 1e-3f));

      // Traces shadow ray
      auto possible_inter = core::closest_intersection(scene, { point, light_vector });
      if (possible_inter.is_initialized() && math::distance(point, possible_inter.get().shape_info.point) < light_distance)
      {
        continue;
      }

      color += info.obj->material->interact(info.shape_info.normal, ray.direction, light_vector) * light.color;
    }

    return color;
  }

  math::vector3d refracted(math::vector3d incident, math::vector3d normal, float n_prev, float n_next) const
  {
    const auto n = n_prev / n_next;
    const auto cosI = -math::dot(normal, incident);
    const auto sinT2 = n * n * (1.0f - cosI * cosI);

    if (sinT2 > 1.0f) return{}; // TIR

    const auto cosT = std::sqrt(1.0f - sinT2);
    return math::scaled(incident, n) + math::scaled(normal, n * cosI - cosT);
  }

  float reflectance(math::vector3d incident, math::vector3d normal, float n_prev, float n_next) const
  {
    const auto n = n_prev / n_next;
    const auto cosI = -math::dot(normal, incident);
    const auto sinT2 = n * n * (1.0f - cosI * cosI);

    if (sinT2 > 1.0f) return 1.0f; // TIR

    const auto cosT = std::sqrt(1.0f - sinT2);
    const auto rOrth = (n_prev * cosI - n_next * cosT) / (n_prev * cosI + n_next * cosT);
    const auto rParl = (n_next * cosI - n_prev * cosT) / (n_next * cosI + n_prev * cosT);

    return (rOrth * rOrth + rParl * rParl) / 2.0f;
  }

  template<typename SceneType>
  graphics::color process_ray(SceneType&& scene, math::ray3d ray, int depth) const
  {
    if (depth >= max_depth)
    {
      return scene.background_color;
    }

    const auto closest_inter = closest_intersection(scene, ray);

    if (closest_inter.is_initialized() == false)
    {
      return scene.background_color;
    }

    auto inter_info = closest_inter.get();

    auto direct_color = shade_direct_lighting(scene, ray, inter_info);

    //return direct_color;

    const auto is_back_side = (0.0f < math::dot(ray.direction, inter_info.shape_info.normal));
    if (is_back_side)
    {
      inter_info.shape_info.normal = -inter_info.shape_info.normal;
    }

    // Calculate reflection contribution.
    graphics::color reflection_color = {};

    const auto n_prev = is_back_side ? inter_info.obj->material.refractive_index : 1.0f;
    const auto n_next = is_back_side ? 1.0f : inter_info.obj->material.refractive_index;

    auto reflection_index = reflectance(ray.direction, inter_info.shape_info.normal, n_prev, n_next);
    if (reflection_index > 0.0f)
    {
      math::ray3d reflection_ray;
      reflection_ray.direction = math::reflected(-ray.direction, inter_info.shape_info.normal);
      reflection_ray.origin = math::translated(inter_info.shape_info.point, math::scaled(reflection_ray.direction, 1e-3f));
      reflection_color = process_ray(scene, reflection_ray, depth + 1);
    }

    // Calculate refraction contribution.
    graphics::color refraction_color = {};

    auto refraction_index = 1.0f - reflection_index;
    if (refraction_index > 0.0f)
    {
      math::ray3d refraction_ray;
      refraction_ray.direction = refracted(ray.direction, inter_info.shape_info.normal, n_prev, n_next);
      refraction_ray.origin = math::translated(inter_info.shape_info.point, math::scaled(refraction_ray.direction, 1e-3f));
      refraction_color = process_ray(scene, refraction_ray, depth + 1);
    }

    auto diffuse_index = 1.0f - reflection_index; // 1.0f - reflection_index - refraction_index;

    return diffuse_index * direct_color + reflection_index * reflection_color;// +refraction_index * refraction_color;
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
        film.add_sample(x, y, process_ray(scene, ray, 0));
      }
    }

    return std::forward<FilmType>(film);
  }
};

}

#endif
