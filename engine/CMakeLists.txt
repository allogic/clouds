cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE ENGINE_SOURCE ${ENGINE_DIR}/*.c)
file(GLOB_RECURSE SANDBOX_SOURCE ${SANDBOX_DIR}/*.c)

add_executable(${PROJECT_NAME} ${ENGINE_SOURCE} ${SANDBOX_SOURCE} ${GLAD_SOURCE})

target_compile_definitions(${PROJECT_NAME}
  PUBLIC _CRT_SECURE_NO_WARNINGS)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${ENGINE_DIR}
  PUBLIC ${SANDBOX_DIR}
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

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/glfw/src/glfw3.dll ${CMAKE_CURRENT_BINARY_DIR}/glfw3.dll)
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/openal/OpenAL32.dll ${CMAKE_CURRENT_BINARY_DIR}/OpenAL32.dll)