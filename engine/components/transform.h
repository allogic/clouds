#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <core/types.h>

typedef enum
{
  transform_dynamic = 0x00000001,
} transform_ctrl_t;

typedef struct
{
  r32m4 model;
  r32v4 local_right;
  r32v4 local_up;
  r32v4 local_front;
  u32 mask;
  i32 transform_parent_id;
  i32 transform_id;
  i32 rigidbody_id;
} transform_t;

#define TRANSFORM_POSITION(TRANSFORM) (TRANSFORM->model[0])
#define TRANSFORM_ROTATION(TRANSFORM) (TRANSFORM->model[1])
#define TRANSFORM_SCALE(TRANSFORM) (TRANSFORM->model[2])

#ifdef __cplusplus
extern "C" {
#endif

  u8 transform_create(transform_t* transform);
  void transform_toggle(transform_t* transform, transform_ctrl_t ctrl);
  void transform_set_position(transform_t* transform, r32 x, r32 y, r32 z);
  void transform_set_rotation(transform_t* transform, r32 x, r32 y, r32 z);
  void transform_set_scale(transform_t* transform, r32 x, r32 y, r32 z);
  void transform_add_position(transform_t* transform, r32 x, r32 y, r32 z);
  void transform_add_rotation(transform_t* transform, r32 x, r32 y, r32 z);
  void transform_add_scale(transform_t* transform, r32 x, r32 y, r32 z);

#ifdef __cplusplus
}
#endif

#endif