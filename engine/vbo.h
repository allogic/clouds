#ifndef VBO_H
#define VBO_H

#include <core/types.h>

typedef struct
{
  u32 count;
  u32 size;
  u32 id;
  void* data;
} vbo_t;

#ifdef __cplusplus
extern "C" {
#endif

  u8 vbo_create(vbo_t* vbo, u32 count, u32 size, void* data);
  void vbo_bind(vbo_t* vbo);
  void vbo_clear(vbo_t* vbo, u32 count);
  void vbo_host_to_device(vbo_t* vbo, u32 count);
  void vbo_device_to_host(vbo_t* vbo, u32 count);
  void vbo_unbind();
  void vbo_destroy(vbo_t* vbo);

#ifdef __cplusplus
}
#endif

#endif