#include <physic.h>
#include <shader.h>
#include <buffer.h>
#include <constants.h>

static shader_t physic_shader =
{
  shader_compute,
  "",
  "",
  ENGINE_ROOT_DIR "shader\\physic\\physic.comp",
};

buffer_t transforms;
buffer_t rigidbodies;

u8 physic_create()
{
  u8 status = 0;
  status |= shader_create(&physic_shader);
  status |= buffer_create(&transforms, buffer_storage, ECS_NUM_ENTITIES, sizeof(transform_t), NULL);
  status |= buffer_create(&rigidbodies, buffer_storage, ECS_NUM_ENTITIES, sizeof(rigidbody_t), NULL);
  return status;
}
void physic_simulate(r32 delta_time)
{
  shader_bind(&physic_shader);
  shader_uniform_r32(&physic_shader, "time", 0.1f);
  buffer_bind(&transforms);
  buffer_sync(&transforms, ECS_NUM_ENTITIES, transfer_to_gpu);
  buffer_unbind(&transforms);
  buffer_bind(&rigidbodies);
  buffer_sync(&rigidbodies, ECS_NUM_ENTITIES, transfer_to_gpu);
  buffer_unbind(&rigidbodies);
  buffer_mount(&transforms, 0);
  buffer_mount(&rigidbodies, 1);
  shader_execute(&physic_shader, 1, 1, ECS_NUM_ENTITY_Z);
  buffer_unmount(&rigidbodies, 1);
  buffer_unmount(&transforms, 0);
  buffer_bind(&rigidbodies);
  buffer_sync(&rigidbodies, ECS_NUM_ENTITIES, transfer_to_cpu);
  buffer_unbind(&rigidbodies);
  buffer_bind(&transforms);
  buffer_sync(&transforms, ECS_NUM_ENTITIES, transfer_to_cpu);
  buffer_unbind(&transforms);
  //ecs_dispatch_physic();
  shader_unbind(&physic_shader);
}
void physic_destroy()
{
  buffer_destroy(&rigidbodies);
  buffer_destroy(&transforms);
  shader_destroy(&physic_shader);
}