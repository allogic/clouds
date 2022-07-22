#include <components/camera.h>

extern r32v2 window_size;

#ifdef __cplusplus
extern "C" {
#endif

  u8 camera_create(camera_t* camera)
  {
    camera->aspect = window_size[0] / window_size[1];
    camera->fov = 45.0f;
    camera->near = 0.001f;
    camera->far = 100000.0f;
    camera->projection[0][0] = 0.0f;
    camera->projection[0][1] = 0.0f;
    camera->projection[0][2] = 0.0f;
    camera->projection[0][3] = 1.0f;
    camera->projection[1][0] = 0.0f;
    camera->projection[1][1] = 0.0f;
    camera->projection[1][2] = 0.0f;
    camera->projection[1][3] = 1.0f;
    camera->projection[2][0] = 0.0f;
    camera->projection[2][1] = 0.0f;
    camera->projection[2][2] = 0.0f;
    camera->projection[2][3] = 1.0f;
    camera->projection[3][0] = 0.0f;
    camera->projection[3][1] = 0.0f;
    camera->projection[3][2] = 0.0f;
    camera->projection[3][3] = 1.0f;
    camera->view[0][0] = 0.0f;
    camera->view[0][1] = 0.0f;
    camera->view[0][2] = 0.0f;
    camera->view[0][3] = 1.0f;
    camera->view[1][0] = 0.0f;
    camera->view[1][1] = 0.0f;
    camera->view[1][2] = 0.0f;
    camera->view[1][3] = 1.0f;
    camera->view[2][0] = 0.0f;
    camera->view[2][1] = 0.0f;
    camera->view[2][2] = 0.0f;
    camera->view[2][3] = 1.0f;
    camera->view[3][0] = 0.0f;
    camera->view[3][1] = 0.0f;
    camera->view[3][2] = 0.0f;
    camera->view[3][3] = 1.0f;
    return 0;
  }

#ifdef __cplusplus
}
#endif