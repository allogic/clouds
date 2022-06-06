#include <string.h>
#include <glad.h>

#include <sbo.h>

u8 sbo_create(sbo_t* sbo, u32 count, u32 size, void* data)
{
  sbo->count = count;
  sbo->size = size;
  glGenBuffers(1, &sbo->id);
  sbo->data = calloc(sbo->count, sbo->size);
  if (sbo->id != 0)
  {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, sbo->id);
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, sbo->count * sbo->size, data, GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);
    if ((sbo->data != NULL) && (data != NULL))
    {
      memcpy(sbo->data, data, sbo->count * sbo->size);
      glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, count * sbo->size, sbo->data);
    }
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return sbo->data == NULL;
  }
  return 1;
}
void sbo_bind(sbo_t* sbo)
{
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, sbo->id);
}
void sbo_mount(sbo_t* sbo, u32 index)
{
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, sbo->id);
}
void sbo_clear(sbo_t* sbo, u32 count)
{
  memset(sbo->data, 0, count * sbo->size);
}
void sbo_host_to_device(sbo_t* sbo, u32 count)
{
  glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, count * sbo->size, sbo->data);
}
void sbo_device_to_host(sbo_t* sbo, u32 count)
{
  glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, count * sbo->size, sbo->data);
}
void sbo_unmount(sbo_t* sbo, u32 index)
{
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, 0);
}
void sbo_unbind()
{
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
void sbo_destroy(sbo_t* sbo)
{
  glDeleteBuffers(1, &sbo->id);
  free(sbo->data);
  sbo->id = 0;
  sbo->data = NULL;
}