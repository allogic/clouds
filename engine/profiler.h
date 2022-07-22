#ifndef PROFILER_H
#define PROFILER_H

#include <glfw/glfw3.h>

#include <core/types.h>

#define PROFILER_NUM_SAMPLES ((u32)512)
#define PROFILER_NUM_FRAMES ((u32)64)

typedef enum
{
  profiler_idx_update = 0,
  profiler_idx_render = 1,
  profiler_idx_physic = 2,
  profiler_idx_sound  = 3,
  profiler_idx_ui     = 4,
} profiler_index_t;

typedef struct
{
  r32 time;
  r32 time_delta;
} profiler_frame_t;

#define PROFILER_FRAME_BEGIN(INDEX)            \
history[0][INDEX].time = ((r32)glfwGetTime()); \

#define PROFILER_FRAME_END(INDEX)                                             \
history[0][INDEX].time_delta = ((r32)glfwGetTime()) - history[0][INDEX].time;

#ifdef __cplusplus
extern "C" {
#endif

  u8 profiler_create();
  void profiler_step();
  void profiler_destroy();

#ifdef __cplusplus
}
#endif

#endif