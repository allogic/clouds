#ifndef RENDERER_H
#define RENDERER_H

#include <core/types.h>

#include <ecs.h>

#ifdef __cplusplus
extern "C" {
#endif

  u8 renderer_create();
  void renderer_render();
  void renderer_destroy();

#ifdef __cplusplus
}
#endif

#endif
