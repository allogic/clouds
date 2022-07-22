#ifndef UPDATE_H
#define UPDATE_H

#include <core/types.h>

#include <ecs.h>

#ifdef __cplusplus
extern "C" {
#endif

  u8 update_create();
  void update_step();
  void update_destroy();

#ifdef __cplusplus
}
#endif

#endif