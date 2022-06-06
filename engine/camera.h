#ifndef CAMERA_H
#define CAMERA_H

#include <core/types.h>

#include <transform.h>

typedef struct
{
  r32 aspect;
  r32 fov;
  r32 near;
  r32 far;
  r32m4 projection;
  r32m4 view;
} camera_t;

#endif