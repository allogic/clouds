#include <string.h>
#include <assert.h>

#include <glad.h>

#include <buffer.h>

u8 buffer_create(buffer_t* buffer, buffer_type_t type, u32 value_count, u32 value_size, void* data)
{
  buffer->type = type;
  buffer->value_count = value_count;
  buffer->value_size = value_size;
  glGenBuffers(1, &buffer->bid);
  if (buffer->bid != 0)
  {
    glBindBuffer(buffer->type, buffer->bid);
    glBufferStorage(buffer->type, buffer->value_count * buffer->value_size, data, GL_DYNAMIC_STORAGE_BIT | GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);
    glBindBuffer(buffer->type, 0);
    buffer->data = calloc(buffer->value_count, buffer->value_size);
    if ((buffer->data != NULL) && (data != NULL))
    {
      memcpy(buffer->data, data, buffer->value_count * buffer->value_size);
    }
    return buffer->data == NULL;
  }
  return 1;
}
void buffer_mount(buffer_t* buffer, u32 index)
{
  assert(buffer->type == buffer_storage || buffer->type == buffer_uniform);
  glBindBufferBase(buffer->type, index, buffer->bid);
}
void buffer_unmount(buffer_t* buffer, u32 index)
{
  assert(buffer->type == buffer_storage || buffer->type == buffer_uniform);
  glBindBufferBase(buffer->type, index, 0);
}
void buffer_bind(buffer_t* buffer)
{
  glBindBuffer(buffer->type, buffer->bid);
}
void buffer_clear(buffer_t* buffer, u32 count)
{
  memset(buffer->data, 0, count * buffer->value_size);
}
void buffer_sync(buffer_t* buffer, u32 count, transfer_t transfer)
{
  switch (transfer)
  {
    case transfer_to_cpu: glGetBufferSubData(buffer->type, 0, count * buffer->value_size, buffer->data); break;
    case transfer_to_gpu: glBufferSubData(buffer->type, 0, count * buffer->value_size, buffer->data); break;
  }
}
void buffer_unbind(buffer_t* buffer)
{
  glBindBuffer(buffer->type, 0);
}
void buffer_destroy(buffer_t* buffer)
{
  glDeleteBuffers(1, &buffer->bid);
  free(buffer->data);
  buffer->bid = 0;
  buffer->data = NULL;
}