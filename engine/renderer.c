#include <glad.h>

#include <renderer.h>
#include <gizmo.h>
#include <shader.h>
#include <constants.h>

static shader_t pbr_shader =
{
  shader_render,
  ENGINE_ROOT_DIR "shader\\render\\pbr.vert",
  ENGINE_ROOT_DIR "shader\\render\\pbr.frag",
};

extern entity_t* player;

void render_queue_proc(entity_t* entity)
{
  transform_t* transform = ECS_TRANSFORM(entity);
  mesh_t* mesh = ECS_MESH(entity);
  shader_uniform_r32m4(&pbr_shader, "model", transform->model);
  mesh_bind(mesh);
  mesh_draw_triangles(mesh, mesh->element_buffers[0].value_count);
  mesh_unbind(mesh);
}

u8 renderer_create()
{
  u8 status = 0;
  status |= gizmo_create();
  status |= shader_create(&pbr_shader);
  ecs_register_static(queue_idx_render, render_queue_proc);
  return status;
}
void renderer_render(r32 delta_time)
{
  if (player != NULL)
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    shader_bind(&pbr_shader);
    shader_uniform_r32m4(&pbr_shader, "projection", ECS_CAMERA(player)->projection);
    shader_uniform_r32m4(&pbr_shader, "view", ECS_CAMERA(player)->view);
    ecs_dispatch_render();
    shader_unbind(&pbr_shader);
    gizmo_render();
  }
}
void renderer_destroy()
{
  shader_destroy(&pbr_shader);
  gizmo_destroy();
}