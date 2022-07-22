#ifndef CAMERA_H
#define CAMERA_H

#include <core/types.h>

typedef struct
{
  r32 aspect;
  r32 fov;
  r32 near;
  r32 far;
  r32m4 projection;
  r32m4 view;
} camera_t;

#ifdef __cplusplus
extern "C" {
#endif

  u8 camera_create(camera_t* camera);

#ifdef __cplusplus
}
#endif

#endif