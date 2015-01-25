SOURCE_GROUP("math" FILES
  ${CMAKE_CURRENT_LIST_DIR}/math/degrees.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/radians.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/trigonometry.hpp
)

SET( APP_SOURCES
  ${APP_SOURCES}
  ${CMAKE_CURRENT_LIST_DIR}/math/degrees.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/point3d.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/radians.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/trigonometry.hpp
  ${CMAKE_CURRENT_LIST_DIR}/math/vector3d.hpp

  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  PARENT_SCOPE
)
