#ifndef FWD_ITERATOR_H
#define FWD_ITERATOR_H

#include <core/types.h>

typedef struct
{
  struct fwd_node_t* head;
  struct fwd_node_t* curr;
  struct fwd_node_t* tail;
} fwd_iter_t;

void fwd_iter_create(fwd_iter_t* iter, struct fwd_list_t* list);
u8 fwd_iter_valid(fwd_iter_t* iter);
void fwd_iter_next(fwd_iter_t* iter);
struct fwd_node_t* fwd_iter_node(fwd_iter_t* iter);
void* fwd_iter_value(fwd_iter_t* iter);

#endif