#include <core/object.hpp>

#include "catch.hpp"

SCENARIO("We can test objects for intersection with rays", "[core][object]")
{
  GIVEN("a object with the shape of a sphere")
  {
    core::object obj;
    obj.shape = { { 0.0f, 0.0f, 0.0f }, 1.0f };
    obj.material = {};

    GIVEN("a ray pointing to the object")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 0.0f, 2.0f }, math::vector3d{ 0.0f, 0.0f, -1.0f } };

      THEN("a intersection is found")
      {
        REQUIRE(core::intersects(obj, ray) == true);
        REQUIRE(core::closest_intersection(obj, ray).is_initialized() == true);
      }
    }

    GIVEN("a ray pointing to the other side")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 0.0f, 2.0f }, math::vector3d{ 0.0f, 0.0f, 1.0f } };

      THEN("no intersection is found")
      {
        REQUIRE(core::intersects(obj, ray) == false);
        REQUIRE(core::closest_intersection(obj, ray).is_initialized() == false);
      }
    }
  }
}