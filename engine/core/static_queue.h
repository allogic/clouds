#ifndef STATIC_QUEUE_H
#define STATIC_QUEUE_H

#include <core/types.h>

typedef struct static_queue_t
{
  u64 head;
  u64 tail;
  u32 length;
  u32 value_count;
  u32 value_size;
  void* data;
} static_queue_t;

void static_queue_create(static_queue_t* queue, u32 value_count, u32 value_size);
u8 static_queue_push(static_queue_t* queue, void* value);
void* static_queue_pop(static_queue_t* queue);
u32 static_queue_length(static_queue_t* queue);
u8 static_queue_empty(static_queue_t* queue);
u8 static_queue_full(static_queue_t* queue);
void static_queue_destroy(static_queue_t* queue);

#endif