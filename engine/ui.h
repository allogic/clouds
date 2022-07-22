#ifndef UI_H
#define UI_H

#include <core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

  u8 ui_create();
  void ui_begin();
  void ui_end();
  void ui_render();
  void ui_destroy();

  void ui_debug_actors(u8* open);
  void ui_debug_profiler(u8* open);

#ifdef __cplusplus
}
#endif

#endif