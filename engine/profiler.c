#include <string.h>

#include <profiler.h>

profiler_frame_t history[PROFILER_NUM_SAMPLES][PROFILER_NUM_FRAMES];

#ifdef __cplusplus
extern "C" {
#endif

  u8 profiler_create()
  {
    u8 status = 0;
    return status;
  }
  void profiler_step()
  {
    for (u32 i = 0; i < (PROFILER_NUM_SAMPLES - 2); i++)
    {
      for (u32 j = 0; j < PROFILER_NUM_FRAMES; j++)
      {
        history[i + 1][j].time = history[i][j].time;
        history[i + 1][j].time_delta = history[i][j].time_delta;
        //memcpy(&history[i + 1][j], &history[i][j], sizeof(profiler_frame_t));
      }
    }
  }
  void profiler_destroy()
  {

  }

#ifdef __cplusplus
}
#endif