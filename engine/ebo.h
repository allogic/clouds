#ifndef EBO_H
#define EBO_H

#include <core/types.h>

typedef struct
{
  u32 count;
  u32 size;
  u32 id;
  void* data;
} ebo_t;

#ifdef __cplusplus
extern "C" {
#endif

  u8 ebo_create(ebo_t* ebo, u32 count, u32 size, void* data);
  void ebo_bind(ebo_t* ebo);
  void ebo_mount(ebo_t* ebo, u32 index);
  void ebo_clear(ebo_t* ebo, u32 count);
  void ebo_host_to_device(ebo_t* ebo, u32 count);
  void ebo_device_to_host(ebo_t* ebo, u32 count);
  void ebo_unmount(ebo_t* ebo, u32 index);
  void ebo_unbind();
  void ebo_destroy(ebo_t* ebo);

#ifdef __cplusplus
}
#endif

#endif