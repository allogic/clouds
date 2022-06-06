cmake_minimum_required(VERSION 3.8)

include(ExternalProject)

project(candbox VERSION 0.0.1 LANGUAGES C)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ENGINE_DIR ${ROOT_DIR}/engine)
set(GLAD_DIR ${ROOT_DIR}/glad)
set(CGLM_DIR ${ROOT_DIR}/cglm)
set(GLFW_DIR ${ROOT_DIR}/glfw)
set(OPENAL_DIR ${ROOT_DIR}/openal)

# OPENGL
find_package(OpenGL REQUIRED)

# GLFW
set(BUILD_SHARED_LIBS ON)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

add_subdirectory(${ROOT_DIR}/glfw)

# GLAD
file(GLOB GLAD_SOURCE ${ROOT_DIR}/glad/*.c)

# CGLM
set(CGLM_SHARED ON)
set(CGLM_STATIC OFF)
set(CGLM_USE_C99 OFF)
set(CGLM_USE_TEST OFF)

add_subdirectory(${ROOT_DIR}/cglm)

# OPENAL
add_subdirectory(${ROOT_DIR}/openal)

# ENGINE
add_subdirectory(engine)