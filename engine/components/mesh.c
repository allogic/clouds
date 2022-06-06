#include <glad.h>

#include <vertex.h>

#include <components/mesh.h>

u8 mesh_create(mesh_t* mesh)
{
  glGenVertexArrays(1, &mesh->vao);
  if (mesh->vao != 0)
  {
    glBindVertexArray(mesh->vao);
    buffer_bind(&mesh->vertex_buffers[0]);
    switch (mesh->type)
    {
      case mesh_line:
      {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_line_t), (void*)(0));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_line_t), (void*)(sizeof(r32v4)));
        break;
      }
      case mesh_text:
      {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_line_t), (void*)(0));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_line_t), (void*)(sizeof(r32v4)));
        break;
      }
      case mesh_pbr:
      {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_pbr_t), (void*)(0));
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_pbr_t), (void*)(sizeof(r32v4)));
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_pbr_t), (void*)(sizeof(r32v4) + (sizeof(r32v4))));
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_pbr_t), (void*)(sizeof(r32v4) + (sizeof(r32v4) + (sizeof(r32v4)))));
        break;
      }
    }
    buffer_bind(&mesh->element_buffers[0]);
    glBindVertexArray(0);
    buffer_unbind(&mesh->vertex_buffers[0]);
    buffer_unbind(&mesh->element_buffers[0]);
    return 0;
  }
  return 1;
}
u8 mesh_push(mesh_t* mesh, u32 vertex_count, u32 vertex_size, u32 element_count, u32 element_size)
{
  u8 status = 0;
  status |= buffer_create(&mesh->vertex_buffers[mesh->sub_count], buffer_vertex, vertex_count, vertex_size, NULL);
  status |= buffer_create(&mesh->element_buffers[mesh->sub_count], buffer_element, element_count, element_size, NULL);
  mesh->sub_count++;
  return status;
}
void mesh_pop(mesh_t* mesh)
{
  mesh->sub_count--;
  buffer_destroy(&mesh->vertex_buffers[mesh->sub_count]);
  buffer_destroy(&mesh->element_buffers[mesh->sub_count]);
}
void mesh_batch(mesh_t* mesh)
{

}
void mesh_assign(mesh_t* mesh)
{

}
void mesh_bind(mesh_t* mesh)
{
  glBindVertexArray(mesh->vao);
}
void mesh_draw_lines(mesh_t* mesh, u32 count)
{
  glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, NULL);
}
void mesh_draw_triangles(mesh_t* mesh, u32 count)
{
  glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
}
void mesh_unbind(mesh_t* mesh)
{
  glBindVertexArray(0);
}
void mesh_destroy(mesh_t* mesh)
{
  glDeleteVertexArrays(1, &mesh->vao);
  mesh->vao = 0;
}