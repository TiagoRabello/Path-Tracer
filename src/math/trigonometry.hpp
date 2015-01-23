#ifndef TRIGONOMETRY_HPP
#define TRIGONOMETRY_HPP

#include "degrees.hpp"
#include "radians.hpp"

#include <cmath>

namespace math
{

const auto pi = 3.14159265359f;

radians to_radians(degrees angle) { return { angle.value * pi / 180.0f }; }
degrees to_degrees(radians angle) { return { angle.value * 180.0f / pi }; }

float sin(radians angle) { return std::sin(angle.value); }
float cos(radians angle) { return std::cos(angle.value); }
float tan(radians angle) { return std::tan(angle.value); }

float sin(degrees angle) { return sin(to_radians(angle)); }
float cos(degrees angle) { return cos(to_radians(angle)); }
float tan(degrees angle) { return tan(to_radians(angle)); }

}

#endif
