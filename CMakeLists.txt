################################################
# CMake App Constants
################################################
SET( MAIN_INCLUDE_DIR        "${CMAKE_CURRENT_LIST_DIR}/src"   )
SET( MAIN_SOURCE_DIR         "${CMAKE_CURRENT_LIST_DIR}/src"   )
SET( TEST_SOURCE_DIR         "${CMAKE_CURRENT_LIST_DIR}/tests" )
SET( APP_NAME                "path_tracer"                     )

################################################
# App Generation Code
################################################
CMAKE_MINIMUM_REQUIRED( VERSION 2.8.7 )
PROJECT( ${APP_NAME} CXX C )

################################################
# App Compiler Flags
################################################
IF( WIN32 )

  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX /W4" )

ELSE( WIN32 )

  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -Werror -Wno-unknown-pragmas -Wno-missing-braces" )

ENDIF( WIN32 )

set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
)

#########################################################
# FIND glfw
#########################################################
FIND_PACKAGE( GLFW )
IF( GLFW_FOUND )

  INCLUDE_DIRECTORIES( ${GLFW_INCLUDE_DIR} )

ELSE( GLFW_FOUND )

  MESSAGE(WARNING "GLFW library was not found. Only tests will be available.")

ENDIF( GLFW_FOUND )

#########################################################
# FIND OpenGL
#########################################################
FIND_PACKAGE( OpenGL )
IF( OPENGL_FOUND )

  INCLUDE_DIRECTORIES( ${OpenGL_INCLUDE_DIRS} )
  LINK_DIRECTORIES   ( ${OpenGL_LIBRARY_DIRS} )
  ADD_DEFINITIONS    ( ${OpenGL_DEFINITIONS}  )

ELSE( OPENGL_FOUND )

  MESSAGE(WARNING "OpenGL library was not found. Only tests will be available.")

ENDIF( OPENGL_FOUND )

#########################################################
# FIND Boost
#########################################################
FIND_PACKAGE(Boost 1.30.0 REQUIRED)

IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
ENDIF()

#########################################################
# App Generation Configuration
#########################################################
INCLUDE_DIRECTORIES( ${MAIN_INCLUDE_DIR} )

IF( GLFW_FOUND AND OPENGL_FOUND )

  ADD_SUBDIRECTORY( ${MAIN_SOURCE_DIR} )
  ADD_EXECUTABLE( ${APP_NAME} ${APP_SOURCES} )

  TARGET_LINK_LIBRARIES( ${APP_NAME}
    ${OPENGL_LIBRARY}
    ${GLFW_LIBRARIES}
    ${Boost_LIBRARIES}
  )

ENDIF( GLFW_FOUND AND OPENGL_FOUND )

#########################################################
# Tests Generation Configuration
#########################################################
ADD_SUBDIRECTORY( ${TEST_SOURCE_DIR} )
ADD_EXECUTABLE( "test_${APP_NAME}" ${TEST_SOURCES} )

TARGET_LINK_LIBRARIES( "test_${APP_NAME}"
  ${Boost_LIBRARIES}
)
