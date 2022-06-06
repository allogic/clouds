cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE ENGINE_SOURCE ${ENGINE_DIR}/*.c)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCE} ${GLAD_SOURCE})

target_compile_definitions(${PROJECT_NAME}
  PUBLIC _CRT_SECURE_NO_WARNINGS)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${ENGINE_DIR}
  PUBLIC ${ROOT_DIR}/glad
  PUBLIC ${ROOT_DIR}/glfw/include/glfw
  PUBLIC ${ROOT_DIR}/cglm/include/cglm)

target_link_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_BINARY_DIR}/glfw/src
  PUBLIC ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME}
  PUBLIC ${OPENGL_LIBRARIES}
  PUBLIC glfw
  PUBLIC cglm)

# TODO: LIB COPY