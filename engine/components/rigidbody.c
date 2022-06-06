#include <components/rigidbody.h>

void rigidbody_identity(rigidbody_t* rigidbody)
{
  rigidbody->position_velocity[0] = 0.0f;
  rigidbody->position_velocity[1] = 0.0f;
  rigidbody->position_velocity[2] = 0.0f;
  rigidbody->position_velocity[3] = 1.0f;
  rigidbody->rotation_velocity[0] = 0.0f;
  rigidbody->rotation_velocity[1] = 0.0f;
  rigidbody->rotation_velocity[2] = 0.0f;
  rigidbody->rotation_velocity[3] = 1.0f;
  rigidbody->position_drag = 0.2f;
  rigidbody->rotation_drag = 0.5f;
  rigidbody->mass = 100.0f;
}
void rigidbody_add_velocity_position(rigidbody_t* rigidbody, r32v4 accel)
{
  rigidbody->position_velocity[0] += accel[0];
  rigidbody->position_velocity[1] += accel[1];
  rigidbody->position_velocity[2] += accel[2];
}
void rigidbody_add_velocity_rotation(rigidbody_t* rigidbody, r32v4 accel)
{
  rigidbody->rotation_velocity[0] += accel[0];
  rigidbody->rotation_velocity[1] += accel[1];
  rigidbody->rotation_velocity[2] += accel[2];
}
void rigidbody_add_velocity_pitch(rigidbody_t* rigidbody, r32 pitch)
{
  rigidbody->rotation_velocity[0] += pitch;
}
void rigidbody_add_velocity_yaw(rigidbody_t* rigidbody, r32 yaw)
{
  rigidbody->rotation_velocity[1] += yaw;
}
void rigidbody_add_velocity_roll(rigidbody_t* rigidbody, r32 roll)
{
  rigidbody->rotation_velocity[2] += roll;
}
void rigidbody_sub_velocity_position(rigidbody_t* rigidbody, r32v4 accel)
{
  rigidbody->position_velocity[0] -= accel[0];
  rigidbody->position_velocity[1] -= accel[1];
  rigidbody->position_velocity[2] -= accel[2];
}
void rigidbody_sub_velocity_rotation(rigidbody_t* rigidbody, r32v4 accel)
{
  rigidbody->rotation_velocity[0] -= accel[0];
  rigidbody->rotation_velocity[1] -= accel[1];
  rigidbody->rotation_velocity[2] -= accel[2];
}
void rigidbody_sub_velocity_pitch(rigidbody_t* rigidbody, r32 pitch)
{
  rigidbody->rotation_velocity[0] -= pitch;
}
void rigidbody_sub_velocity_yaw(rigidbody_t* rigidbody, r32 yaw)
{
  rigidbody->rotation_velocity[1] -= yaw;
}
void rigidbody_sub_velocity_roll(rigidbody_t* rigidbody, r32 roll)
{
  rigidbody->rotation_velocity[2] -= roll;
}