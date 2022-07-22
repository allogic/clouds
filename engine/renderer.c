#include <glad/glad.h>

#include <renderer.h>
#include <pbr.h>
#include <gizmo.h>

extern entity_t* player;

#ifdef __cplusplus
extern "C" {
#endif

  u8 renderer_create()
  {
    u8 status = 0;
    status |= pbr_create();
    status |= gizmo_create();
    return status;
  }
  void renderer_render()
  {
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    pbr_render();
    //gizmo_render();
  }
  void renderer_destroy()
  {
    gizmo_destroy();
    pbr_destroy();
  }

#ifdef __cplusplus
}
#endif