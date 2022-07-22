#ifndef PBR_H
#define PBR_H

#include <core/types.h>

#include <ecs.h>

#ifdef __cplusplus
extern "C" {
#endif

  u8 pbr_create();
  void pbr_render();
  void pbr_destroy();

#ifdef __cplusplus
}
#endif

#endif