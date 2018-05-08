#include <core/physics.hpp>

#include "catch.hpp"

SCENARIO("We can calculate the refracted vector", "[core][physics]")
{
  GIVEN("a surface normal and a 45 degrees incident vector")
  {
    math::vector3d normal = { 0.0f, 1.0f, 0.0f };
    math::vector3d incident = math::normalized({ -1.0f, -1.0f, 0.0f });

    GIVEN("the same refraction index for both mediums")
    {
      auto n1 = 1.5f;
      auto n2 = 1.5f;

      THEN("refracted vector is equal to incident vector")
      {
        auto answer = core::refracted(incident, normal, n1, n2);

        REQUIRE(answer == incident);
      }
    }

    GIVEN("an outgoing refraction index that is 1.5x the previous index")
    {
      auto n1 = 1.0f;
      auto n2 = 1.5f;

      THEN("refracted vector follows snell's law")
      {
        auto answer = core::refracted(incident, normal, n1, n2);

        auto sinT = n1 / n2 * incident.x;
        auto cosT = std::signbit(incident.y) ? -sqrt(1.0f - sinT * sinT) : sqrt(1.0f - sinT * sinT);
        math::vector3d expected = { sinT, cosT };
        REQUIRE(answer == expected);
      }
    }
  }
}