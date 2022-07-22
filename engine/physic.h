#ifndef PHYSIC_H
#define PHYSIC_H

#include <core/types.h>

#include <ecs.h>

#ifdef __cplusplus
extern "C" {
#endif

  u8 physic_create();
  void physic_step(r32 steps_size);
  void physic_destroy();

#ifdef __cplusplus
}
#endif

#endif