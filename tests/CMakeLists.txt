SET( TEST_SOURCES
  ${TEST_SOURCES}
  ${CMAKE_CURRENT_LIST_DIR}/tests_main.cpp

  ${CMAKE_CURRENT_LIST_DIR}/tests_core_intersection_info.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests_core_object.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests_core_scene.cpp

  ${CMAKE_CURRENT_LIST_DIR}/tests_math_point3d.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests_math_trigonometry.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests_math_utility.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tests_math_vector3d.cpp

  ${CMAKE_CURRENT_LIST_DIR}/tests_shapes_sphere.cpp

  PARENT_SCOPE
)
