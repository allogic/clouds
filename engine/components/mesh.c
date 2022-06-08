#include <glad/glad.h>

#include <vertex.h>

#include <components/mesh.h>

u8 mesh_create(mesh_t* mesh)
{
  glGenVertexArrays(1, &mesh->vao);
  if (mesh->vao != 0)
  {
    return 0;
  }
  return 1;
}
u8 mesh_push(mesh_t* mesh, u32 vertex_count, u32 vertex_size, u32 element_count, u32 element_size)
{
  u8 status = 0;
  status |= vbo_create(&mesh->vbos[mesh->sub_count], vertex_count, vertex_size, NULL);
  status |= ebo_create(&mesh->ebos[mesh->sub_count], element_count, element_size, NULL);
  mesh->sub_count++;
  return status;
}
u8 mesh_pop(mesh_t* mesh)
{
  u8 status = 0;
  mesh->sub_count--;
  vbo_destroy(&mesh->vbos[mesh->sub_count]);
  ebo_destroy(&mesh->ebos[mesh->sub_count]);
  return status;
}
u8 mesh_select_layout(mesh_t* mesh, u32 index, mesh_layout_t layout)
{
  u8 status = 0;
  glBindVertexArray(mesh->vao);
  vbo_bind(&mesh->vbos[index]);
  switch (layout)
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
  ebo_bind(&mesh->ebos[index]);
  glBindVertexArray(0);
  vbo_unbind();
  ebo_unbind();
  return status;
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
void mesh_unbind()
{
  glBindVertexArray(0);
}
void mesh_destroy(mesh_t* mesh)
{
  glDeleteVertexArrays(1, &mesh->vao);
  mesh->vao = 0;
}