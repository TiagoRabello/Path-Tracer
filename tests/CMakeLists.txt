SET( TEST_SOURCES
  ${TEST_SOURCES}
  ${CMAKE_CURRENT_LIST_DIR}/tests_main.cpp

  ${CMAKE_CURRENT_LIST_DIR}/tests_cameras_pinhole_camera.cpp

  ${CMAKE_CURRENT_LIST_DIR}/tests_core_intersection_info.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests_core_object.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests_core_scene.cpp

  ${CMAKE_CURRENT_LIST_DIR}/tests_lights_point_light.cpp

  ${CMAKE_CURRENT_LIST_DIR}/tests_math_coordinate_system.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests_math_monte_carlo_integrator.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests_math_point3d.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests_math_trigonometry.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests_math_utility.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests_math_vector3d.cpp

  ${CMAKE_CURRENT_LIST_DIR}/tests_shapes_sphere.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests_shapes_triangle.cpp

  PARENT_SCOPE
)
