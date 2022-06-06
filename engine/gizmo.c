#include <string.h>

#include <ecs.h>
#include <gizmo.h>
#include <shader.h>
#include <vertex.h>
#include <constants.h>

#include <components/camera.h>
#include <components/mesh.h>

extern entity_t* player;

static shader_t line_shader =
{
  shader_render,
  ENGINE_ROOT_DIR "shader\\gizmo\\line.vert",
  ENGINE_ROOT_DIR "shader\\gizmo\\line.frag",
};
static shader_t text_shader =
{
  shader_render,
  ENGINE_ROOT_DIR "shader\\gizmo\\text.vert",
  ENGINE_ROOT_DIR "shader\\gizmo\\text.frag",
};

static mesh_t line_mesh =
{
  mesh_line,
};
static mesh_t text_mesh =
{
  mesh_text,
};

static u32 line_vertex_offset = 0;
static u32 line_element_offset = 0;

static u32 prev_line_vertex_offset = 0;
static u32 prev_line_element_offset = 0;

u8 gizmo_create()
{
  u8 status = 0;
  status |= shader_create(&line_shader);
  status |= shader_create(&text_shader);
  status |= mesh_push(&line_mesh, GIZMO_NUM_VERTEX_LINE, sizeof(vertex_line_t), GIZMO_NUM_VERTEX_LINE * 2, sizeof(u32));
  status |= mesh_push(&text_mesh, GIZMO_NUM_VERTEX_TEXT, sizeof(vertex_text_t), GIZMO_NUM_VERTEX_TEXT * 2, sizeof(u32));
  status |= mesh_create(&line_mesh);
  status |= mesh_create(&text_mesh);
  return status;
}
void gizmo_push_line(r32v3 a, r32v3 b, r32v4 c)
{
  vertex_line_t vertices[2] =
  {
    { { a[0], a[1], a[2], 1.0f }, { c[0], c[1], c[2], c[3] } },
    { { b[0], b[1], b[2], 1.0f }, { c[0], c[1], c[2], c[3] } },
  };
  u32 elements[2] =
  {
    line_vertex_offset + 0,
    line_vertex_offset + 1,
  };
  memcpy(((vertex_line_t*)line_mesh.vertex_buffers[0].data) + line_vertex_offset, vertices, sizeof(vertices));
  memcpy(((u32*)line_mesh.element_buffers[0].data) + line_element_offset, elements, sizeof(elements));
  line_vertex_offset += 2;
  line_element_offset += 2;
}
void gizmo_push_box(r32v3 p, r32v3 s, r32v4 c)
{
  vertex_line_t vertices[8] =
  {
    { { (p[0] + -s[0]), (p[1] + -s[1]), (p[2] + -s[2]), 1.0f }, { c[0], c[1], c[2], c[3] } },
    { { (p[0] +  s[0]), (p[1] + -s[1]), (p[2] + -s[2]), 1.0f }, { c[0], c[1], c[2], c[3] } },
    { { (p[0] + -s[0]), (p[1] +  s[1]), (p[2] + -s[2]), 1.0f }, { c[0], c[1], c[2], c[3] } },
    { { (p[0] +  s[0]), (p[1] +  s[1]), (p[2] + -s[2]), 1.0f }, { c[0], c[1], c[2], c[3] } },
    { { (p[0] + -s[0]), (p[1] + -s[1]), (p[2] +  s[2]), 1.0f }, { c[0], c[1], c[2], c[3] } },
    { { (p[0] +  s[0]), (p[1] + -s[1]), (p[2] +  s[2]), 1.0f }, { c[0], c[1], c[2], c[3] } },
    { { (p[0] + -s[0]), (p[1] +  s[1]), (p[2] +  s[2]), 1.0f }, { c[0], c[1], c[2], c[3] } },
    { { (p[0] +  s[0]), (p[1] +  s[1]), (p[2] +  s[2]), 1.0f }, { c[0], c[1], c[2], c[3] } },
  };
  u32 elements[24] =
  {
    line_vertex_offset + 0,
    line_vertex_offset + 1,
    line_vertex_offset + 0,
    line_vertex_offset + 2,
    line_vertex_offset + 2,
    line_vertex_offset + 3,
    line_vertex_offset + 3,
    line_vertex_offset + 1,
    line_vertex_offset + 4,
    line_vertex_offset + 5,
    line_vertex_offset + 4,
    line_vertex_offset + 6,
    line_vertex_offset + 6,
    line_vertex_offset + 7,
    line_vertex_offset + 7,
    line_vertex_offset + 5,
    line_vertex_offset + 0,
    line_vertex_offset + 4,
    line_vertex_offset + 1,
    line_vertex_offset + 5,
    line_vertex_offset + 2,
    line_vertex_offset + 6,
    line_vertex_offset + 3,
    line_vertex_offset + 7,
  };
  memcpy(((vertex_line_t*)line_mesh.vertex_buffers[0].data) + line_vertex_offset, vertices, sizeof(vertices));
  memcpy(((u32*)line_mesh.element_buffers[0].data) + line_element_offset, elements, sizeof(elements));
  line_vertex_offset += 8;
  line_element_offset += 24;
}
void gizmo_push_sphere(r32v3 p, r32 radius, u32 segments, r32v4 c)
{
  //vertex_line_t* vertices = malloc(sizeof(vertex_line_t) * segments * 3);
  //u32* elements = malloc(sizeof(u32) * segments * 3);
  //r32 d, r, x, y;
  //u32 j, k;
  //if ((vertices != NULL) && (elements != NULL))
  //{
  //  j = segments;
  //  k = segments * 2;
  //  for (u32 i = 0; i < segments; i++)
  //  {
  //    d = i * (360.0f / segments);
  //    r = d * (3.14159265f / 180.0f);
  //    x = sinf(r) * radius;
  //    y = sinf(r) * radius;
  //    vertices[i].position[0] = x;
  //    vertices[i].position[1] = y;
  //    vertices[i].position[2] = 0.0f;
  //    vertices[i].color[0] = 1.0f;
  //    vertices[i].color[1] = 0.0f;
  //    vertices[i].color[2] = 0.0f;
  //    vertices[i].color[3] = 1.0f;
  //    elements[j] = line_vertex_offset + i;
  //    vertices[j].position[0] = x;
  //    vertices[j].position[1] = 0.0f;
  //    vertices[j].position[2] = y;
  //    vertices[j].color[0] = 1.0f;
  //    vertices[j].color[1] = 0.0f;
  //    vertices[j].color[2] = 0.0f;
  //    vertices[j].color[3] = 1.0f;
  //    elements[j] = line_vertex_offset + j;
  //    vertices[k].position[0] = 0.0f;
  //    vertices[k].position[1] = y;
  //    vertices[k].position[2] = x;
  //    vertices[k].color[0] = 1.0f;
  //    vertices[k].color[1] = 0.0f;
  //    vertices[k].color[2] = 0.0f;
  //    vertices[k].color[3] = 1.0f;
  //    elements[k] = line_vertex_offset + k;
  //  };
  //  memcpy(line_mesh.vertex_buffers[0].data, vertices, sizeof(vertices));
  //  memcpy(line_mesh.element_buffers[0].data, elements, sizeof(elements));
  //  free(vertices);
  //  free(elements);
  //  line_vertex_offset += segments * 3;
  //  line_element_offset += segments * 3;
  //}
}
void gizmo_push_text(r32v3 p, r32v3 s, i8 const* str, r32v4 c)
{

}
void gizmo_render()
{
  shader_bind(&line_shader);
  shader_uniform_r32m4(&line_shader, "projection", ECS_CAMERA(player)->projection);
  shader_uniform_r32m4(&line_shader, "view", ECS_CAMERA(player)->view);
  mesh_bind(&line_mesh);
  buffer_bind(&line_mesh.vertex_buffers[0]);
  //buffer_clear(&line_mesh.vertex_buffers[0], prev_line_vertex_offset);
  buffer_sync(&line_mesh.vertex_buffers[0], line_vertex_offset, transfer_to_gpu);
  buffer_bind(&line_mesh.element_buffers[0]);
  //buffer_clear(&line_mesh.element_buffers[0], prev_line_element_offset);
  buffer_sync(&line_mesh.element_buffers[0], line_element_offset, transfer_to_gpu);
  mesh_draw_lines(&line_mesh, line_element_offset);
  buffer_unbind(&line_mesh.element_buffers[0]);
  buffer_unbind(&line_mesh.vertex_buffers[0]);
  mesh_unbind(&line_mesh);
  shader_unbind(&line_shader);
  prev_line_vertex_offset = line_vertex_offset;
  prev_line_element_offset = line_element_offset;
  line_vertex_offset = 0;
  line_element_offset = 0;
}
void gizmo_destroy()
{
  mesh_destroy(&text_mesh);
  mesh_destroy(&line_mesh);
  shader_destroy(&text_shader);
  shader_destroy(&line_shader);
}