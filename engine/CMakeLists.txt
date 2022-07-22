cmake_minimum_required(VERSION 3.8)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE ENGINE_SOURCE ${ENGINE_DIR}/*.c ${ENGINE_DIR}/*.cpp)
file(GLOB_RECURSE SANDBOX_SOURCE ${SANDBOX_DIR}/*.c)
file(GLOB_RECURSE ALUT_SOURCE ${ALUT_DIR}/src/*.c)
file(GLOB GLAD_SOURCE ${GLAD_DIR}/glad.c)
file(GLOB UFBX_SOURCE ${UFBX_DIR}/ufbx.c)
file(GLOB IMGUI_SOURCE ${IMGUI_DIR}/*.cpp ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)
file(GLOB IMPLOT_SOURCE ${IMPLOT_DIR}/*.cpp)

add_executable(${PROJECT_NAME}
  ${ENGINE_SOURCE}
  ${SANDBOX_SOURCE}
  ${GLAD_SOURCE}
  ${ALUT_SOURCE}
  ${UFBX_SOURCE}
  ${IMGUI_SOURCE}
  ${IMPLOT_SOURCE}
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${ROOT_DIR}/bin
  LIBRARY_OUTPUT_DIRECTORY ${ROOT_DIR}/bin
  RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR}/bin
)

target_compile_definitions(${PROJECT_NAME}
  PUBLIC _CRT_SECURE_NO_WARNINGS
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${ROOT_DIR}
  PUBLIC ${ENGINE_DIR}
  PUBLIC ${SANDBOX_DIR}
  PUBLIC ${GLFW_DIR}/include
  PUBLIC ${CGLM_DIR}/include
  PUBLIC ${OPENAL_DIR}/include
  PUBLIC ${ALUT_DIR}/include
  PUBLIC ${IMGUI_DIR}
)

target_link_directories(${PROJECT_NAME}
  PUBLIC ${BIN_DIR}
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC ${OPENGL_LIBRARIES}
  PUBLIC glfw
  PUBLIC cglm
  PUBLIC openal
)