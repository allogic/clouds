#ifndef MESH_H
#define MESH_H

#include <core/types.h>

#include <buffer.h>

typedef enum
{
  mesh_line,
  mesh_text,
  mesh_pbr,
} mesh_type_t;

typedef struct
{
  mesh_type_t type;
  buffer_t vertex_buffers[256];
  buffer_t element_buffers[256];
  u32 sub_count;
  u32 vao;
} mesh_t;

u8 mesh_create(mesh_t* mesh);
u8 mesh_push(mesh_t* mesh, u32 vertex_count, u32 vertex_size, u32 element_count, u32 element_size);
void mesh_pop(mesh_t* mesh);
void mesh_batch(mesh_t* mesh);
void mesh_assign(mesh_t* mesh);
void mesh_bind(mesh_t* mesh);
void mesh_draw_lines(mesh_t* mesh, u32 count);
void mesh_draw_triangles(mesh_t* mesh, u32 count);
void mesh_unbind(mesh_t* mesh);
void mesh_destroy(mesh_t* mesh);

#endif