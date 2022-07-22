#ifndef FWD_LIST_H
#define FWD_LIST_H

#include <core/types.h>
#include <core/fwd_iterator.h>

typedef struct fwd_node_t
{
  struct fwd_node_t* next;
  struct fwd_node_t* data;
} fwd_node_t;

typedef struct fwd_list_t
{
  struct fwd_node_t* head;
  struct fwd_node_t* tail;
  u32 count;
} fwd_list_t;

#ifdef __cplusplus
extern "C" {
#endif

  void fwd_list_create(fwd_list_t* list);
  void* fwd_list_push(fwd_list_t* list, void* data, u32 size);
  void fwd_list_erase(fwd_list_t* list, void* data);
  void fwd_list_destroy(fwd_list_t* list);

#ifdef __cplusplus
}
#endif

#endif