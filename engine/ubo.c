#include <string.h>

#include <glad/glad.h>

#include <ubo.h>

u8 ubo_create(ubo_t* ubo, u32 count, u32 size, void* data)
{
  ubo->count = count;
  ubo->size = size;
  glGenBuffers(1, &ubo->id);
  ubo->data = calloc(ubo->count, ubo->size);
  if (ubo->id != 0)
  {
    glBindBuffer(GL_UNIFORM_BUFFER, ubo->id);
    glBufferStorage(GL_UNIFORM_BUFFER, ubo->count * ubo->size, data, GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);
    if ((ubo->data != NULL) && (data != NULL))
    {
      memcpy(ubo->data, data, ubo->count * ubo->size);
      glBufferSubData(GL_UNIFORM_BUFFER, 0, count * ubo->size, ubo->data);
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    return ubo->data == NULL;
  }
  return 1;
}
void ubo_bind(ubo_t* ubo)
{
  glBindBuffer(GL_UNIFORM_BUFFER, ubo->id);
}
void ubo_mount(ubo_t* ubo, u32 index)
{
  glBindBufferBase(GL_UNIFORM_BUFFER, index, ubo->id);
}
void ubo_clear(ubo_t* ubo, u32 count)
{
  memset(ubo->data, 0, count * ubo->size);
}
void ubo_host_to_device(ubo_t* ubo, u32 count)
{
  glBufferSubData(GL_UNIFORM_BUFFER, 0, count * ubo->size, ubo->data);
}
void ubo_device_to_host(ubo_t* ubo, u32 count)
{
  glGetBufferSubData(GL_UNIFORM_BUFFER, 0, count * ubo->size, ubo->data);
}
void ubo_unmount(ubo_t* ubo, u32 index)
{
  glBindBufferBase(GL_UNIFORM_BUFFER, index, 0);
}
void ubo_unbind()
{
  glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
void ubo_destroy(ubo_t* ubo)
{
  glDeleteBuffers(1, &ubo->id);
  free(ubo->data);
  ubo->id = 0;
  ubo->data = NULL;
}