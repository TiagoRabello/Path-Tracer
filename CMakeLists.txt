################################################
# CMake App Constants
################################################
SET( MAIN_INCLUDE_DIR        "${CMAKE_CURRENT_LIST_DIR}/src"   )
SET( MAIN_SOURCE_DIR         "${CMAKE_CURRENT_LIST_DIR}/src"   )
SET( TEST_SOURCE_DIR         "${CMAKE_CURRENT_LIST_DIR}/tests" )
SET( APP_NAME                "path_tracer_demo"                )
SET( LIB_NAME                "path_tracer_lib"                 )
SET( TEST_NAME               "path_tracer_test"                )

################################################
# App Generation Code
################################################
CMAKE_MINIMUM_REQUIRED( VERSION 2.8.7 )
PROJECT( "path_tracer" CXX C )

################################################
# App Compiler Flags
################################################
IF( WIN32 )

  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX /W4" )
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4702" ) # Necessary for catch to compile cleanly

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
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

# Setup and Get Projects Sources/Headers
INCLUDE_DIRECTORIES( ${MAIN_INCLUDE_DIR} )
ADD_SUBDIRECTORY( ${MAIN_SOURCE_DIR} )

#########################################################
# Library Generation Configuration
#########################################################
ADD_LIBRARY(${LIB_NAME} STATIC ${LIB_SOURCES})

TARGET_LINK_LIBRARIES( ${LIB_NAME}
  ${Boost_LIBRARIES}
)

#########################################################
# App Generation Configuration
#########################################################
IF( GLFW_FOUND AND OPENGL_FOUND )

  ADD_EXECUTABLE( ${APP_NAME} ${APP_SOURCES} )

  TARGET_LINK_LIBRARIES( ${APP_NAME}
    ${LIB_NAME}
    ${OPENGL_LIBRARY}
    ${GLFW_LIBRARIES}
    ${Boost_LIBRARIES}
  )

ENDIF( GLFW_FOUND AND OPENGL_FOUND )

#########################################################
# Tests Generation Configuration
#########################################################
ADD_SUBDIRECTORY( ${TEST_SOURCE_DIR} )
ADD_EXECUTABLE( ${TEST_NAME} ${TEST_SOURCES} )

TARGET_LINK_LIBRARIES( ${TEST_NAME}
  ${LIB_NAME}
  ${Boost_LIBRARIES}
)

# Setup Projects Source Groups
INCLUDE("${MAIN_SOURCE_DIR}/CMakeSourceGroups.txt")
