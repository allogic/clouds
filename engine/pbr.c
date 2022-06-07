#include <pbr.h>
#include <ecs.h>
#include <shader.h>
#include <constants.h>

extern entity_t* player;

static shader_t pbr_shader =
{
  shader_render,
  ENGINE_ROOT_DIR "shader\\render\\pbr.vert",
  ENGINE_ROOT_DIR "shader\\render\\pbr.frag",
};

void pbr_queue_proc(entity_t* entity)
{
  transform_t* transform = ECS_TRANSFORM(entity);
  mesh_t* mesh = ECS_MESH(entity);
  shader_uniform_r32m4(&pbr_shader, "model", transform->model);
  mesh_bind(mesh);
  mesh_draw_triangles(mesh, mesh->ebos[0].count);
  mesh_unbind(mesh);
  ecs_call_available_procedures(entity, dispatch_pbr);
}

u8 pbr_create()
{
  u8 status = 0;
  status |= shader_create(&pbr_shader);
  status |= ecs_register_static(queue_idx_pbr, pbr_queue_proc);
  return status;
}
void pbr_render()
{
  if (player != NULL)
  {
    shader_bind(&pbr_shader);
    shader_uniform_r32m4(&pbr_shader, "projection", ECS_CAMERA(player)->projection);
    shader_uniform_r32m4(&pbr_shader, "view", ECS_CAMERA(player)->view);
    ecs_dispatch_pbr();
    shader_unbind(&pbr_shader);
  }
}
void pbr_destroy()
{
  shader_destroy(&pbr_shader);
}