#include <string.h>
#include <glad.h>

#include <vbo.h>

u8 vbo_create(vbo_t* vbo, u32 count, u32 size, void* data)
{
  vbo->count = count;
  vbo->size = size;
  glGenBuffers(1, &vbo->id);
  vbo->data = calloc(vbo->count, vbo->size);
  if (vbo->id != 0)
  {
    glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
    glBufferStorage(GL_ARRAY_BUFFER, vbo->count * vbo->size, data, GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);
    if ((vbo->data != NULL) && (data != NULL))
    {
      memcpy(vbo->data, data, vbo->count * vbo->size);
      glBufferSubData(GL_ARRAY_BUFFER, 0, count * vbo->size, vbo->data);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo->data == NULL;
  }
  return 1;
}
void vbo_bind(vbo_t* vbo)
{
  glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
}
void vbo_clear(vbo_t* vbo, u32 count)
{
  memset(vbo->data, 0, count * vbo->size);
}
void vbo_host_to_device(vbo_t* vbo, u32 count)
{
  glBufferSubData(GL_ARRAY_BUFFER, 0, count * vbo->size, vbo->data);
}
void vbo_device_to_host(vbo_t* vbo, u32 count)
{
  glGetBufferSubData(GL_ARRAY_BUFFER, 0, count * vbo->size, vbo->data);
}
void vbo_unbind()
{
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void vbo_destroy(vbo_t* vbo)
{
  glDeleteBuffers(1, &vbo->id);
  free(vbo->data);
  vbo->id = 0;
  vbo->data = NULL;
}