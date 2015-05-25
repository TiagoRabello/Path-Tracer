#ifndef MATH_TRIGONOMETRY_HPP
#define MATH_TRIGONOMETRY_HPP

#include "degrees.hpp"
#include "radians.hpp"

#include <cmath>

namespace math
{

const auto pi = 3.14159265359f;

inline radians to_radians(degrees angle) { return { angle.value * pi / 180.0f }; }
inline degrees to_degrees(radians angle) { return { angle.value * 180.0f / pi }; }

inline float sin(radians angle) { return std::sin(angle.value); }
inline float cos(radians angle) { return std::cos(angle.value); }
inline float tan(radians angle) { return std::tan(angle.value); }

inline float sin(degrees angle) { return sin(to_radians(angle)); }
inline float cos(degrees angle) { return cos(to_radians(angle)); }
inline float tan(degrees angle) { return tan(to_radians(angle)); }

}

#endif
