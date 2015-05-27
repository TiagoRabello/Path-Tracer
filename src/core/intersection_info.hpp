#ifndef CORE_INTERSECTION_INFO_HPP
#define CORE_INTERSECTION_INFO_HPP

#include <shapes/intersection_info.hpp>

#include <tuple>

namespace core
{

struct object; // From core/object.hpp

struct intersection_info
{
  shapes::intersection_info shape_info;
  const object *obj;
};

inline bool operator==(intersection_info lhs, intersection_info rhs)
{
  return std::tie(lhs.shape_info, lhs.obj)
      == std::tie(rhs.shape_info, rhs.obj);
}

inline bool operator!=(intersection_info lhs, intersection_info rhs)
{
  return !(lhs == rhs);
}

}

#endif
