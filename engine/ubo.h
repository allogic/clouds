#ifndef UBO_H
#define UBO_H

#include <core/types.h>

typedef struct
{
  u32 count;
  u32 size;
  u32 id;
  void* data;
} ubo_t;

#ifdef __cplusplus
extern "C" {
#endif

  u8 ubo_create(ubo_t* ubo, u32 count, u32 size, void* data);
  void ubo_bind(ubo_t* ubo);
  void ubo_mount(ubo_t* ubo, u32 index);
  void ubo_clear(ubo_t* ubo, u32 count);
  void ubo_host_to_device(ubo_t* ubo, u32 count);
  void ubo_device_to_host(ubo_t* ubo, u32 count);
  void ubo_unmount(ubo_t* ubo, u32 index);
  void ubo_unbind();
  void ubo_destroy(ubo_t* ubo);

#ifdef __cplusplus
}
#endif

#endif