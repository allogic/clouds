#include <string.h>

#include <core/fwd_list.h>

static u8 fwd_node_create(fwd_node_t** node, void* data, u32 size)
{
  (*node) = calloc(1, sizeof(fwd_node_t));
  if ((*node) != NULL)
  {
    if (data == NULL)
    {
      (*node)->data = calloc(1, size);
    }
    else
    {
      (*node)->data = malloc(size);
      if ((*node)->data != NULL)
      {
        memcpy((*node)->data, data, size);
      }
    }
    return (*node)->data == NULL;
  }
  return 1;
}
static void fwd_node_destroy(fwd_node_t** node)
{
  if (node != NULL)
  {
    if ((*node) != NULL)
    {
      if ((*node)->data != NULL)
      {
        free((*node)->data);
        (*node)->data = NULL;
      }
      free(*node);
      (*node) = NULL;
    }
  }
}

#ifdef __cplusplus
extern "C" {
#endif

  void fwd_list_create(fwd_list_t* list)
  {
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
  }
  void* fwd_list_push(fwd_list_t* list, void* data, u32 size)
  {
    if (list->head == NULL)
    {
      if (fwd_node_create(&list->head, data, size) == 0)
      {
        list->tail = list->head;
        list->count++;
      }
    }
    else if (list->tail != NULL)
    {
      if (fwd_node_create(&((fwd_node_t*)list->tail->next), data, size) == 0)
      {
        list->tail = list->tail->next;
        list->count++;
      }
    }
    if (list->tail != NULL)
    {
      return list->tail->data;
    }
    return NULL;
  }
  void fwd_list_erase(fwd_list_t* list, void* data)
  {
    fwd_node_t* curr = list->head;
    fwd_node_t* next = list->head->next;
    fwd_node_t* prev = list->head;
    while (curr != NULL)
    {
      if (curr->data == data)
      {
        if (curr == list->head)
        {
          list->head = list->head->next;
          if (list->head != NULL)
          {
            if (list->head->next == NULL)
            {
              list->tail = list->head;
            }
          }
        }
        else
        {
          prev->next = curr->next;
        }
        fwd_node_destroy(&curr);
        list->count--;
        break;
      }
      prev = curr;
      curr = next;
      if (curr != NULL)
      {
        next = curr->next;
      }
    }
  }
  void fwd_list_destroy(fwd_list_t* list)
  {
    if (list->head != NULL)
    {
      fwd_node_t* curr = list->head;
      fwd_node_t* next = list->head->next;
      while (curr != NULL)
      {
        fwd_node_destroy(&curr);
        list->count--;
        curr = next;
        if (curr != NULL)
        {
          next = curr->next;
        }
      }
      list->head = NULL;
      list->tail = NULL;
    }
  }

#ifdef __cplusplus
}
#endif