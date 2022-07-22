#ifndef QUEUE_ITERATOR_H
#define QUEUE_ITERATOR_H

#include <core/types.h>

typedef struct
{
  u64 head;
  u64 curr;
  u64 tail;
  u32 value_count;
  u32 value_size;
  void* data;
} queue_iter_t;

#ifdef __cplusplus
extern "C" {
#endif

  void queue_iter_create(queue_iter_t* iter, struct static_queue_t* queue);
  u8 queue_iter_valid(queue_iter_t* iter);
  void queue_iter_next(queue_iter_t* iter);
  u32 queue_iter_index(queue_iter_t* iter);
  void* queue_iter_value(queue_iter_t* iter);

#ifdef __cplusplus
}
#endif

#endif