SET( LIB_SOURCES
  ${LIB_SOURCES}

  ${CMAKE_CURRENT_LIST_DIR}/brdfs/lambertian.hpp

  ${CMAKE_CURRENT_LIST_DIR}/cameras/pinhole_camera.cpp
  ${CMAKE_CURRENT_LIST_DIR}/cameras/pinhole_camera.hpp

  ${CMAKE_CURRENT_LIST_DIR}/core/intersection_info.hpp
  ${CMAKE_CURRENT_LIST_DIR}/core/material.hpp
  ${CMAKE_CURRENT_LIST_DIR}/core/object.hpp
  ${CMAKE_CURRENT_LIST_DIR}/core/scene.cpp
  ${CMAKE_CURRENT_LIST_DIR}/core/scene.hpp

  ${CMAKE_CURRENT_LIST_DIR}/films/component_buffer_film.hpp

  ${CMAKE_CURRENT_LIST_DIR}/graphics/color.hpp

  ${CMAKE_CURRENT_LIST_DIR}/lights/point_light.hpp

  ${CMAKE_CURRENT_LIST_DIR}/math/coordinate_system.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/degrees.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/monte_carlo_integrator.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/point3d.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/radians.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/ray3d.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/trigonometry.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/utility.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/vector3d.hpp

  ${CMAKE_CURRENT_LIST_DIR}/renderers/normal_renderer.hpp
  ${CMAKE_CURRENT_LIST_DIR}/renderers/raycaster.hpp
  ${CMAKE_CURRENT_LIST_DIR}/renderers/path_tracer.hpp

  ${CMAKE_CURRENT_LIST_DIR}/shapes/intersection_info.hpp
  ${CMAKE_CURRENT_LIST_DIR}/shapes/plane.cpp
  ${CMAKE_CURRENT_LIST_DIR}/shapes/plane.hpp
  ${CMAKE_CURRENT_LIST_DIR}/shapes/quadrilateral.cpp
  ${CMAKE_CURRENT_LIST_DIR}/shapes/quadrilateral.hpp
  ${CMAKE_CURRENT_LIST_DIR}/shapes/sphere.cpp
  ${CMAKE_CURRENT_LIST_DIR}/shapes/sphere.hpp
  ${CMAKE_CURRENT_LIST_DIR}/shapes/triangle.cpp
  ${CMAKE_CURRENT_LIST_DIR}/shapes/triangle.hpp
  PARENT_SCOPE
)

SET( APP_SOURCES
  ${APP_SOURCES}

  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  PARENT_SCOPE
)
