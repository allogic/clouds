#include <update.h>
#include <ecs.h>

static void update_queue_proc(entity_t* entity)
{
  ecs_call_available_procedures(entity, dispatch_update);
}

#ifdef __cplusplus
extern "C" {
#endif

  u8 update_create()
  {
    u8 status = 0;
    status |= ecs_register_static(queue_idx_update, update_queue_proc);
    return status;
  }
  void update_step()
  {
    ecs_dispatch_update();

    // TODO: impl nice timer stuff

    //prev_fps_time = (r32)glfwGetTime();
    //fps_count++;
    //if ((time - prev_fps_time) > 1.0f)
    //{
    //  sprintf_s(fps_title, sizeof(fps_title), "%u", fps_count);
    //  glfwSetWindowTitle(window, fps_title);
    //  fps_count = 0;
    //  prev_fps_time = (r32)glfwGetTime();
    //}
  }
  void update_destroy()
  {

  }

#ifdef __cplusplus
}
#endif