#include <stdio.h>
#include <assert.h>

#include <core/fwd_list.h>
#include <core/queue_iterator.h>

#include <ecs.h>
#include <physic.h>
#include <buffer.h>

static u32 unique_id = 0;
static u32 transform_id = 0;
static u32 rigidbody_id = 0;

static fwd_list_t entities;

static static_queue_t update_queue;
static static_queue_t physic_queue;
static static_queue_t render_queue;

static queue_proc_t procedures[64];

extern buffer_t transforms;
extern buffer_t rigidbodies;

u8 ecs_create()
{
  fwd_list_create(&entities);
  static_queue_create(&update_queue, ECS_QUEUE_SIZE_UPDATE, sizeof(entity_t*));
  static_queue_create(&physic_queue, ECS_QUEUE_SIZE_PHYSIC, sizeof(entity_t*));
  static_queue_create(&render_queue, ECS_QUEUE_SIZE_RENDER, sizeof(entity_t*));
  return 0;
}
entity_t* ecs_push()
{
  entity_t* entity = fwd_list_push(&entities, NULL, sizeof(entity_t));
  if (entity != NULL)
  {
    entity->id = unique_id++;
  }
  return entity;
}
void ecs_erase(entity_t* entity)
{
  fwd_list_erase(&entities, entity);
}
transform_t* ecs_attach_transform(entity_t* entity)
{
  entity->components[comp_idx_transform] = &((transform_t*)transforms.data)[transform_id++];
  entity->comp_mask |= comp_bit_transform;
  transform_identity(ECS_TRANSFORM(entity));
  return ECS_TRANSFORM(entity);
}
camera_t* ecs_attach_camera(entity_t* entity)
{
  entity->components[comp_idx_camera] = calloc(1, sizeof(camera_t));
  entity->comp_mask |= comp_bit_camera;
  return ECS_CAMERA(entity);
}
mesh_t* ecs_attach_mesh(entity_t* entity)
{
  entity->components[comp_idx_mesh] = calloc(1, sizeof(mesh_t));
  entity->comp_mask |= comp_bit_mesh;
  return ECS_MESH(entity);
}
rigidbody_t* ecs_attach_rigidbody(entity_t* entity)
{
  ECS_TRANSFORM(entity)->rigidbody_id = rigidbody_id;
  entity->components[comp_idx_rigidbody] = &((rigidbody_t*)rigidbodies.data)[rigidbody_id++];
  entity->comp_mask |= comp_bit_rigibody;
  rigidbody_identity(ECS_RIGIDBODY(entity));
  ECS_TRANSFORM(entity)->mask |= transform_dynamic;
  return ECS_RIGIDBODY(entity);
}
void ecs_register_static(u32 queue_idx, queue_proc_t proc)
{
  procedures[queue_idx] = proc;
}
void ecs_register_dynamic(entity_t* entity, u32 proc_idx, u64 proc_bit, queue_proc_t proc)
{
  entity->procedures[proc_idx] = proc;
  entity->proc_mask |= proc_bit;
}
void ecs_update_queues(entity_t* entity)
{
  u8 status = 0;
  if ((entity->comp_mask & queue_mask_update) == queue_mask_update) status |= static_queue_push(&update_queue, &entity);
  if ((entity->comp_mask & queue_mask_physic) == queue_mask_physic) status |= static_queue_push(&physic_queue, &entity);
  if ((entity->comp_mask & queue_mask_render) == queue_mask_render) status |= static_queue_push(&render_queue, &entity);
  if (status != 0)
  {
    printf("Queue drop detected\n");
  }
}
void ecs_dispatch(static_queue_t* queue, u32 queue_idx, dispatch_t dispatch_type)
{
  entity_t* entity = NULL;
  queue_iter_t iter;
  queue_iter_create(&iter, queue);
  while (queue_iter_valid(&iter) == 0)
  {
    entity = *(entity_t**)queue_iter_value(&iter);
    if (procedures[queue_idx] != NULL) procedures[queue_idx](entity);
    switch (dispatch_type)
    {
      case dispatch_update:
        if ((entity->proc_mask & event_mask_update) == event_mask_update) ((queue_proc_t)entity->procedures[event_idx_update])(entity);
        break;
      case dispatch_render:
        if ((entity->proc_mask & event_mask_gizmo) == event_mask_gizmo) ((queue_proc_t)entity->procedures[event_idx_gizmo])(entity);
        break;
      case dispatch_physic:
        break;
    }
    queue_iter_next(&iter);
  }
}
void ecs_dispatch_update()
{
  ecs_dispatch(&update_queue, queue_idx_update, dispatch_update);
}
void ecs_dispatch_physic()
{
  ecs_dispatch(&physic_queue, queue_idx_physic, dispatch_physic);
}
void ecs_dispatch_render()
{
  ecs_dispatch(&render_queue, queue_idx_render, dispatch_render);
}
void ecs_destroy()
{
  static_queue_destroy(&render_queue);
  static_queue_destroy(&physic_queue);
  static_queue_destroy(&update_queue);
  fwd_list_destroy(&entities);
}