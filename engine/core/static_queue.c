#include <string.h>

#include <core/static_queue.h>

#ifdef __cplusplus
extern "C" {
#endif

  void static_queue_create(static_queue_t* queue, u32 value_count, u32 value_size)
  {
    queue->head = 0;
    queue->tail = 0;
    queue->length = 0;
    queue->value_count = value_count;
    queue->value_size = value_size;
    queue->data = calloc(value_count, value_size);
  }
  u8 static_queue_push(static_queue_t* queue, void* value)
  {
    if (static_queue_full(queue))
    {
      return 1;
    }
    memcpy((u8*)queue->data + queue->tail, value, queue->value_size);
    queue->length++;
    queue->tail = (queue->tail + queue->value_size) % ((u64)queue->value_count * queue->value_size);
    return 0;
  }
  void* static_queue_pop(static_queue_t* queue)
  {
    u8* value = NULL;
    if (static_queue_empty(queue))
    {
      return NULL;
    }
    value = (u8*)queue->data + queue->head;
    queue->head = (queue->head + queue->value_size) % ((u64)queue->value_count * queue->value_size);
    queue->length--;
    return value;
  }
  u32 static_queue_length(static_queue_t* queue)
  {
    return queue->length;
  }
  u8 static_queue_empty(static_queue_t* queue)
  {
    return queue->length == 0;
  }
  u8 static_queue_full(static_queue_t* queue)
  {
    return queue->length >= queue->value_count;
  }
  void static_queue_destroy(static_queue_t* queue)
  {
    queue->tail = 0;
    queue->head = 0;
    queue->length = 0;
    queue->value_count = 0;
    queue->value_size = 0;
    free(queue->data);
    queue->data = NULL;
  }

#ifdef __cplusplus
}
#endif