cmake_minimum_required(VERSION 3.8)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE ENGINE_SOURCE ${ENGINE_DIR}/*.c)
file(GLOB_RECURSE SANDBOX_SOURCE ${SANDBOX_DIR}/*.c)
file(GLOB_RECURSE GLAD_SOURCE ${GLAD_DIR}/*.c)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCE} ${SANDBOX_SOURCE} ${GLAD_SOURCE})

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
  PUBLIC ${ENGINE_DIR}
  PUBLIC ${SANDBOX_DIR}
  PUBLIC ${GLAD_DIR}
  PUBLIC ${GLFW_DIR}/include/glfw
  PUBLIC ${CGLM_DIR}/include/cglm
  PUBLIC ${OPENAL_DIR}/include/AL
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