#include <core/fwd_iterator.h>
#include <core/fwd_list.h>

void fwd_iter_create(fwd_iter_t* iter, fwd_list_t* list)
{
  if (list->count > 0)
  {
    iter->head = list->head;
    iter->curr = list->head;
    iter->tail = list->tail;
  }
  else
  {
    iter->head = NULL;
    iter->curr = NULL;
    iter->tail = NULL;
  }
}
u8 fwd_iter_valid(fwd_iter_t* iter)
{
  return iter->curr == NULL;
}
void fwd_iter_next(fwd_iter_t* iter)
{
  if (iter->curr != NULL)
  {
    iter->curr = iter->curr->next;
  }
}
fwd_node_t* fwd_iter_node(fwd_iter_t* iter)
{
  return iter->curr;
}
void* fwd_iter_value(fwd_iter_t* iter)
{
  return iter->curr->data;
}