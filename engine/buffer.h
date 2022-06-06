#ifndef BUFFER_H
#define BUFFER_H

#include <core/types.h>

typedef enum
{
  buffer_storage = 0x90D2,
  buffer_uniform = 0x8A11,
  buffer_vertex = 0x8892,
  buffer_element = 0x8893,
} buffer_type_t;

typedef enum
{
  transfer_to_cpu,
  transfer_to_gpu,
} transfer_t;

typedef struct
{
  buffer_type_t type;
  u32 value_count;
  u32 value_size;
  u32 bid;
  void* data;
} buffer_t;

u8 buffer_create(buffer_t* buffer, buffer_type_t type, u32 value_count, u32 value_size, void* data);
void buffer_mount(buffer_t* buffer, u32 index);
void buffer_unmount(buffer_t* buffer, u32 index);
void buffer_bind(buffer_t* buffer);
void buffer_clear(buffer_t* buffer, u32 count);
void buffer_sync(buffer_t* buffer, u32 count, transfer_t transfer);
void buffer_unbind(buffer_t* buffer);
void buffer_destroy(buffer_t* buffer);

#endif