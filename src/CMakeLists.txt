SOURCE_GROUP("core" FILES
  ${CMAKE_CURRENT_LIST_DIR}/core/intersection_info.hpp
  ${CMAKE_CURRENT_LIST_DIR}/core/material.hpp
  ${CMAKE_CURRENT_LIST_DIR}/core/object.hpp
  ${CMAKE_CURRENT_LIST_DIR}/core/scene.hpp
)

SOURCE_GROUP("graphics" FILES
  ${CMAKE_CURRENT_LIST_DIR}/graphics/color.hpp
)

SOURCE_GROUP("lights" FILES
  ${CMAKE_CURRENT_LIST_DIR}/lights/point_light.hpp
)

SOURCE_GROUP("math" FILES
  ${CMAKE_CURRENT_LIST_DIR}/math/degrees.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/point3d.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/radians.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/ray3d.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/trigonometry.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/utility.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/vector3d.hpp
)

SOURCE_GROUP("shapes" FILES
  ${CMAKE_CURRENT_LIST_DIR}/shapes/sphere.hpp
)

SET( LIB_SOURCES
  ${LIB_SOURCES}

  ${CMAKE_CURRENT_LIST_DIR}/core/intersection_info.hpp
  ${CMAKE_CURRENT_LIST_DIR}/core/material.hpp
  ${CMAKE_CURRENT_LIST_DIR}/core/object.hpp
  ${CMAKE_CURRENT_LIST_DIR}/core/scene.hpp
  
  ${CMAKE_CURRENT_LIST_DIR}/graphics/color.hpp

  ${CMAKE_CURRENT_LIST_DIR}/lights/point_light.hpp
  
  ${CMAKE_CURRENT_LIST_DIR}/math/degrees.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/point3d.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/radians.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/ray3d.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/trigonometry.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/utility.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/vector3d.hpp

  ${CMAKE_CURRENT_LIST_DIR}/shapes/sphere.hpp
  PARENT_SCOPE
)

SET( APP_SOURCES
  ${APP_SOURCES}

  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  PARENT_SCOPE
)
