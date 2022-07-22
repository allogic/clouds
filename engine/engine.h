#ifndef ENGINE_H
#define ENGINE_H

#include <core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

  void engine_update();
  void engine_render();
  void engine_physic();
  void engine_sound();
  void engine_ui();

#ifdef __cplusplus
}
#endif

i32 main();

#endif