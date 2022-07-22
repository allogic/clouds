#ifndef SBO_H
#define SBO_H

#include <core/types.h>

typedef struct
{
  u32 count;
  u32 size;
  u32 id;
  void* data;
} sbo_t;

#ifdef __cplusplus
extern "C" {
#endif

  u8 sbo_create(sbo_t* sbo, u32 count, u32 size, void* data);
  void sbo_bind(sbo_t* sbo);
  void sbo_mount(sbo_t* sbo, u32 index);
  void sbo_clear(sbo_t* sbo, u32 count);
  void sbo_host_to_device(sbo_t* sbo, u32 count);
  void sbo_device_to_host(sbo_t* sbo, u32 count);
  void sbo_unmount(sbo_t* sbo, u32 index);
  void sbo_unbind();
  void sbo_destroy(sbo_t* sbo);

#ifdef __cplusplus
}
#endif

#endif