#ifndef PLAYER_H
#define PLAYER_H

#include <core/types.h>

#include <ecs.h>

#ifdef __cplusplus
extern "C" {
#endif

  u8 player_create();
  void player_break(rigidbody_t* rigidbody);
  void player_boost(transform_t* transform, rigidbody_t* rigidbody);
  void player_drift(transform_t* transform, rigidbody_t* rigidbody);
  void player_destroy();

#ifdef __cplusplus
}
#endif

#endif