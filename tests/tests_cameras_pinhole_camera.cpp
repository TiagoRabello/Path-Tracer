#include "cameras/pinhole_camera.hpp"

#include "math/ray3d.hpp"
#include "math/utility.hpp"

#include "catch.hpp"

SCENARIO("We can get rays from a pinhole camera", "[cameras][pinhole_camera]")
{
  GIVEN("a camera centered at the origin looking down the x axis")
  {
    auto eye = math::point3d{ 0.0f, 0.0f, 0.0f };
    auto at = math::point3d{ 1.0f, 0.0f, 0.0f };
    auto up = math::vector3d{ 0.0f, 1.0f, 0.0f };
    auto fovy = math::degrees{ 45.0f };
    auto nearp = 1.0f;
    auto farp = 100.0f;
    auto film_width = 600.0f;
    auto film_height = 400.0f;

    cameras::pinhole_camera camera{ eye, at, up, fovy, nearp, farp, film_width, film_height };

    THEN("a ray can be generated from the center of the eye")
    {
      auto ray = camera.generate_ray(film_width / 2.0f, film_height / 2.0f);
      auto expected_dir = math::make_vector3d(eye, at);
      
      REQUIRE(ray.origin == eye);
      REQUIRE(ray.direction == expected_dir);
    }
  }
}