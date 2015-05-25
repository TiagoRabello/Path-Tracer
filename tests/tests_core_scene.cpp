#include <core/scene.hpp>

#include "catch.hpp"

SCENARIO("We can test scenes for intersection with rays", "[core][scene]")
{
  GIVEN("a scene with two objects")
  {
    core::scene scene;

    core::object obj1;
    obj1.shape = { { 0.0f, 0.0f, 0.0f }, 1.0f };
    scene.add(obj1);

    core::object obj2;
    obj2.shape = { { 0.0f, 2.0f, 0.0f }, 1.0f };
    scene.add(obj2);

    GIVEN("a ray pointing to the first object")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 0.0f, 2.0f }, math::vector3d{ 0.0f, 0.0f, -1.0f } };

      THEN("a intersection with the first object is found")
      {
        REQUIRE(core::intersects(scene, ray) == true);

        auto possible_info = core::closest_intersection(scene, ray);
        REQUIRE(possible_info.is_initialized() == true);
        REQUIRE(*(possible_info.get().obj) == obj1);
      }
    }

    GIVEN("a ray pointing to the second object")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 2.0f, 2.0f }, math::vector3d{ 0.0f, 0.0f, -1.0f } };

      THEN("a intersection with the second object is found")
      {
        REQUIRE(core::intersects(scene, ray) == true);

        auto possible_info = core::closest_intersection(scene, ray);
        REQUIRE(possible_info.is_initialized() == true);
        REQUIRE(*(possible_info.get().obj) == obj2);
      }
    }

    GIVEN("a ray pointing to the first object through the second one")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 4.0f, 0.0f }, math::vector3d{ 0.0f, -1.0f, 0.0f } };

      THEN("a intersection with the first object is found")
      {
        REQUIRE(core::intersects(scene, ray) == true);

        auto possible_info = core::closest_intersection(scene, ray);
        REQUIRE(possible_info.is_initialized() == true);
        REQUIRE(*(possible_info.get().obj) == obj2);
      }
    }

    GIVEN("a ray pointing to the second object through the first one")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, -2.0f, 0.0f }, math::vector3d{ 0.0f, 1.0f, 0.0f } };

      THEN("a intersection with the first object is found")
      {
        REQUIRE(core::intersects(scene, ray) == true);

        auto possible_info = core::closest_intersection(scene, ray);
        REQUIRE(possible_info.is_initialized() == true);
        REQUIRE(*(possible_info.get().obj) == obj1);
      }
    }

    GIVEN("a ray pointing to no object")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 4.0f, 2.0f }, math::vector3d{ 0.0f, 0.0f, -1.0f } };

      THEN("no intersection is found")
      {
        REQUIRE(core::intersects(scene, ray) == false);
        REQUIRE(core::closest_intersection(scene, ray).is_initialized() == false);
      }
    }
  }

  GIVEN("a empty scene")
  {
    core::scene scene;

    GIVEN("a ray")
    {
      auto ray = math::ray3d{ math::point3d{ 0.0f, 0.0f, 0.0f }, math::vector3d{ 0.0f, 0.0f, 0.0f } };

      THEN("no intersection is found")
      {
        REQUIRE(core::intersects(scene, ray) == false);
        REQUIRE(core::closest_intersection(scene, ray).is_initialized() == false);
      }
    }
  }
}