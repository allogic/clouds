#ifndef MESH_H
#define MESH_H

#include <core/types.h>

#include <assets.h>

typedef enum
{
  mesh_line,
  mesh_text,
  mesh_pbr,
} mesh_layout_t;

typedef struct
{
  u32 vao;
} mesh_t;

#ifdef __cplusplus
extern "C" {
#endif

  u8 mesh_create(mesh_t* mesh);
  u8 mesh_push(mesh_t* mesh, u32 vertex_count, u32 vertex_size, u32 element_count, u32 element_size);
  u8 mesh_pop(mesh_t* mesh);
  u8 mesh_select_layout(mesh_t* mesh, u32 index, mesh_layout_t layout);
  u8 mesh_from(mesh_t* mesh, model_t* model);
  void mesh_batch(mesh_t* mesh);
  void mesh_bind(mesh_t* mesh);
  void mesh_draw_lines(mesh_t* mesh, u32 count);
  void mesh_draw_triangles(mesh_t* mesh, u32 count);
  void mesh_unbind();
  void mesh_destroy(mesh_t* mesh);

#ifdef __cplusplus
}
#endif

#endif