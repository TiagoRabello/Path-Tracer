#include "math/coordinate_system.hpp"

#include <vector>

#include "catch.hpp"

SCENARIO( "We can generate an orthogonal coordinate system from a single vector", "[math][coordinate_system]")
{
  GIVEN("a valid unit vector in 3d space")
  {
    auto x = math::vector3d{ 1.0f, 0.0f, 0.0f };

    THEN("we can get a orthogonal system")
    {
      const auto system = math::make_coordinate_system(x);
      REQUIRE(x == system.v1);
      REQUIRE(math::length(system.v2) - 1.0f < 1e-10);
      REQUIRE(math::length(system.v3) - 1.0f < 1e-10);
      REQUIRE(math::dot(system.v1, system.v2) < 1e-10);
      REQUIRE(math::dot(system.v1, system.v3) < 1e-10);
      REQUIRE(math::dot(system.v2, system.v3) < 1e-10);
    }
  }
}