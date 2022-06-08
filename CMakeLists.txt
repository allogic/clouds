cmake_minimum_required(VERSION 3.8)

project(clouds VERSION 0.0.1 LANGUAGES C)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BIN_DIR ${ROOT_DIR}/bin)
set(ENGINE_DIR ${ROOT_DIR}/engine)
set(SHADER_DIR ${ROOT_DIR}/shader)
set(SANDBOX_DIR ${ROOT_DIR}/sandbox)
set(GLAD_DIR ${ROOT_DIR}/glad)
set(CGLM_DIR ${ROOT_DIR}/cglm)
set(GLFW_DIR ${ROOT_DIR}/glfw)
set(OPENAL_DIR ${ROOT_DIR}/openal)
set(ALUT_DIR ${ROOT_DIR}/alut)

add_subdirectory(engine)