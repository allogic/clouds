#include <physic.h>
#include <shader.h>
#include <constants.h>
#include <sbo.h>

static shader_t physic_shader =
{
  shader_compute,
  "",
  "",
  ENGINE_ROOT_DIR "shader\\physic\\physic.comp",
};

sbo_t transforms;
sbo_t rigidbodies;

void physic_queue_proc(entity_t* entity)
{
  ecs_call_available_procedures(entity, dispatch_physic);
}

u8 physic_create()
{
  u8 status = 0;
  status |= shader_create(&physic_shader);
  status |= sbo_create(&transforms, ECS_NUM_ENTITIES, sizeof(transform_t), NULL);
  status |= sbo_create(&rigidbodies, ECS_NUM_ENTITIES, sizeof(rigidbody_t), NULL);
  status |= ecs_register_static(queue_idx_physic, physic_queue_proc);
  return status;
}
void physic_step(r32 steps_size)
{
  shader_bind(&physic_shader);
  shader_uniform_r32(&physic_shader, "steps_size", steps_size);
  sbo_bind(&transforms);
  sbo_host_to_device(&transforms, ECS_NUM_ENTITIES);
  sbo_bind(&rigidbodies);
  sbo_host_to_device(&rigidbodies, ECS_NUM_ENTITIES);
  sbo_mount(&transforms, 0);
  sbo_mount(&rigidbodies, 1);
  shader_execute(&physic_shader, 1, 1, ECS_NUM_ENTITY_Z);
  sbo_unmount(&rigidbodies, 1);
  sbo_unmount(&transforms, 0);
  sbo_bind(&rigidbodies);
  sbo_device_to_host(&rigidbodies, ECS_NUM_ENTITIES);
  sbo_bind(&transforms);
  sbo_device_to_host(&transforms, ECS_NUM_ENTITIES);
  sbo_unbind();
  ecs_dispatch_physic();
  shader_unbind(&physic_shader);
}
void physic_destroy()
{
  sbo_destroy(&rigidbodies);
  sbo_destroy(&transforms);
  shader_destroy(&physic_shader);
}