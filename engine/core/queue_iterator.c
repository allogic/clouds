#include <core/queue_iterator.h>
#include <core/static_queue.h>

void queue_iter_create(queue_iter_t* iter, static_queue_t* queue)
{
  iter->head = queue->head;
  iter->curr = queue->head;
  iter->tail = queue->tail;
  iter->value_count = queue->value_count;
  iter->value_size = queue->value_size;
  iter->data = queue->data;
}
u8 queue_iter_valid(queue_iter_t* iter)
{
  return iter->curr >= iter->tail;
}
void queue_iter_next(queue_iter_t* iter)
{
  iter->curr = (iter->curr + iter->value_size) % ((u64)iter->value_count * iter->value_size);
}
u32 queue_iter_index(queue_iter_t* iter)
{
  return (u32)((iter->curr - iter->head) / iter->value_size);
}
void* queue_iter_value(queue_iter_t* iter)
{
  return (u8*)iter->data + iter->curr;
}