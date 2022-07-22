#ifndef SOUND_H
#define SOUND_H

#include <core/types.h>

#include <ecs.h>

#ifdef __cplusplus
extern "C" {
#endif

  u8 sound_create();
  void sound_step();
  void sound_destroy();

#ifdef __cplusplus
}
#endif

#endif