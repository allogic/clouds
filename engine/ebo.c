#include <string.h>

#include <glad/glad.h>

#include <ebo.h>

#ifdef __cplusplus
extern "C" {
#endif

  u8 ebo_create(ebo_t* ebo, u32 count, u32 size, void* data)
  {
    ebo->count = count;
    ebo->size = size;
    glGenBuffers(1, &ebo->id);
    ebo->data = calloc(ebo->count, ebo->size);
    if (ebo->id != 0)
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->id);
      glBufferStorage(GL_ELEMENT_ARRAY_BUFFER, ebo->count * ebo->size, data, GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);
      if ((ebo->data != NULL) && (data != NULL))
      {
        memcpy(ebo->data, data, ebo->count * ebo->size);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * ebo->size, ebo->data);
      }
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      return ebo->data == NULL;
    }
    return 1;
  }
  void ebo_bind(ebo_t* ebo)
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->id);
  }
  void ebo_mount(ebo_t* ebo, u32 index)
  {
    glBindBufferBase(GL_ELEMENT_ARRAY_BUFFER, index, ebo->id);
  }
  void ebo_clear(ebo_t* ebo, u32 count)
  {
    memset(ebo->data, 0, count * ebo->size);
  }
  void ebo_host_to_device(ebo_t* ebo, u32 count)
  {
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * ebo->size, ebo->data);
  }
  void ebo_device_to_host(ebo_t* ebo, u32 count)
  {
    glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * ebo->size, ebo->data);
  }
  void ebo_unmount(ebo_t* ebo, u32 index)
  {
    glBindBufferBase(GL_ELEMENT_ARRAY_BUFFER, index, 0);
  }
  void ebo_unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }
  void ebo_destroy(ebo_t* ebo)
  {
    glDeleteBuffers(1, &ebo->id);
    free(ebo->data);
    ebo->id = 0;
    ebo->data = NULL;
  }

#ifdef __cplusplus
}
#endif