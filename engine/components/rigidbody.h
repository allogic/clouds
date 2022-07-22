#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <core/types.h>

typedef struct
{
  r32v4 position_velocity;
  r32v4 rotation_velocity;
  r32 position_drag;
  r32 rotation_drag;
  r32 mass;
  i32 rigidbody_id;
} rigidbody_t;

#ifdef __cplusplus
extern "C" {
#endif

  u8 rigidbody_create(rigidbody_t* rigidbody);
  void rigidbody_add_velocity_position(rigidbody_t* rigidbody, r32v4 accel);
  void rigidbody_add_velocity_rotation(rigidbody_t* rigidbody, r32v4 accel);
  void rigidbody_add_velocity_pitch(rigidbody_t* rigidbody, r32 pitch);
  void rigidbody_add_velocity_yaw(rigidbody_t* rigidbody, r32 yaw);
  void rigidbody_add_velocity_roll(rigidbody_t* rigidbody, r32 roll);
  void rigidbody_sub_velocity_position(rigidbody_t* rigidbody, r32v4 accel);
  void rigidbody_sub_velocity_rotation(rigidbody_t* rigidbody, r32v4 accel);
  void rigidbody_sub_velocity_pitch(rigidbody_t* rigidbody, r32 pitch);
  void rigidbody_sub_velocity_yaw(rigidbody_t* rigidbody, r32 yaw);
  void rigidbody_sub_velocity_roll(rigidbody_t* rigidbody, r32 roll);

#ifdef __cplusplus
}
#endif

#endif