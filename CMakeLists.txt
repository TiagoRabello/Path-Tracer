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
FIND_PACKAGE( GLFW REQUIRED )
INCLUDE_DIRECTORIES( ${GLFW_INCLUDE_DIR} )

#########################################################
# FIND glm
#########################################################
FIND_PACKAGE( GLM REQUIRED )
INCLUDE_DIRECTORIES( ${GLM_INCLUDE_DIRS} )

#########################################################
# FIND OpenGL
#########################################################
FIND_PACKAGE( OpenGL REQUIRED )
INCLUDE_DIRECTORIES( ${OpenGL_INCLUDE_DIRS} )
LINK_DIRECTORIES   ( ${OpenGL_LIBRARY_DIRS} )
ADD_DEFINITIONS    ( ${OpenGL_DEFINITIONS}  )

#########################################################
# App Generation Configuration
#########################################################
INCLUDE_DIRECTORIES( ${MAIN_INCLUDE_DIR} )

ADD_SUBDIRECTORY( ${MAIN_SOURCE_DIR} )
ADD_EXECUTABLE( ${APP_NAME} ${APP_SOURCES} )

TARGET_LINK_LIBRARIES( ${APP_NAME}
  ${OPENGL_LIBRARY}
  ${GLFW_LIBRARIES}
)

#########################################################
# Tests Generation Configuration
#########################################################
ADD_SUBDIRECTORY( ${TEST_SOURCE_DIR} )
ADD_EXECUTABLE( "test_${APP_NAME}" ${TEST_SOURCES} )
