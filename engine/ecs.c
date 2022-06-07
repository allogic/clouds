#include <string.h>
#include <assert.h>

#include <core/fwd_list.h>
#include <core/queue_iterator.h>

#include <ecs.h>
#include <physic.h>
#include <sbo.h>

static u32 unique_id = 0;
static u32 transform_id = 0;
static u32 rigidbody_id = 0;

static fwd_list_t entities;

static static_queue_t update_queue;
static static_queue_t physic_queue;
static static_queue_t gizmo_queue;
static static_queue_t pbr_queue;

static queue_proc_t procedures[64];

extern sbo_t transforms;
extern sbo_t rigidbodies;

u8 ecs_create()
{
  fwd_list_create(&entities);
  static_queue_create(&update_queue, ECS_UPDATE_QUEUE_SIZE, sizeof(entity_t*));
  static_queue_create(&physic_queue, ECS_PHYSIC_QUEUE_SIZE, sizeof(entity_t*));
  static_queue_create(&gizmo_queue, ECS_GIZMO_QUEUE_SIZE, sizeof(entity_t*));
  static_queue_create(&pbr_queue, ECS_PBR_QUEUE_SIZE, sizeof(entity_t*));
  return 0;
}
entity_t* ecs_create_entity()
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
transform_t* ecs_attach_transform(entity_t* entity, u8* status)
{
  entity->components[comp_idx_transform] = &((transform_t*)transforms.data)[transform_id++];
  entity->comp_mask |= comp_bit_transform;
  *status |= transform_create(ECS_TRANSFORM(entity));
  assert(*status == 0);
  return ECS_TRANSFORM(entity);
}
camera_t* ecs_attach_camera(entity_t* entity, u8* status)
{
  entity->components[comp_idx_camera] = calloc(1, sizeof(camera_t));
  entity->comp_mask |= comp_bit_camera;
  *status |= camera_create(ECS_CAMERA(entity));
  assert(*status == 0);
  return ECS_CAMERA(entity);
}
mesh_t* ecs_attach_mesh(entity_t* entity, u8* status)
{
  entity->components[comp_idx_mesh] = calloc(1, sizeof(mesh_t));
  entity->comp_mask |= comp_bit_mesh;
  *status |= mesh_create(ECS_MESH(entity));
  assert(*status == 0);
  return ECS_MESH(entity);
}
rigidbody_t* ecs_attach_rigidbody(entity_t* entity, u8* status)
{
  ECS_TRANSFORM(entity)->rigidbody_id = rigidbody_id;
  entity->components[comp_idx_rigidbody] = &((rigidbody_t*)rigidbodies.data)[rigidbody_id++];
  entity->comp_mask |= comp_bit_rigibody;
  *status |= rigidbody_create(ECS_RIGIDBODY(entity));
  ECS_TRANSFORM(entity)->mask |= transform_dynamic;
  assert(*status == 0);
  return ECS_RIGIDBODY(entity);
}
audio_listener_t* ecs_attach_audio_listener(entity_t* entity, u8* status)
{
  entity->components[comp_idx_audio_listener] = calloc(1, sizeof(audio_listener_t));
  entity->comp_mask |= comp_bit_audio_listener;
  *status |= audio_listener_create(ECS_AUDIO_LISTENER(entity));
  assert(*status == 0);
  return ECS_AUDIO_LISTENER(entity);
}
audio_source_t* ecs_attach_audio_source(entity_t* entity, u8* status)
{
  entity->components[comp_idx_audio_source] = calloc(1, sizeof(audio_source_t));
  entity->comp_mask |= comp_bit_audio_source;
  *status |= audio_source_create(ECS_AUDIO_SOURCE(entity));
  assert(*status == 0);
  return ECS_AUDIO_SOURCE(entity);
}
u8 ecs_register_static(u32 index, queue_proc_t proc)
{
  if (procedures[index] == NULL)
  {
    procedures[index] = proc;
    return 0;
  }
  return 1;
}
u8 ecs_register_dynamic(entity_t* entity, u32 index, u64 bit, queue_proc_t proc)
{
  if (entity->procedures[index] == NULL)
  {
    entity->procedures[index] = proc;
    entity->proc_mask |= bit;
    return 0;
  }
  return 1;
}
u8 ecs_update_queues(entity_t* entity)
{
  u8 status = 0;
  if ((entity->comp_mask & queue_mask_update) == queue_mask_update) status |= static_queue_push(&update_queue, &entity);
  if ((entity->comp_mask & queue_mask_physic) == queue_mask_physic) status |= static_queue_push(&physic_queue, &entity);
  if ((entity->comp_mask & queue_mask_gizmo) == queue_mask_gizmo) status |= static_queue_push(&gizmo_queue, &entity);
  if ((entity->comp_mask & queue_mask_pbr) == queue_mask_pbr) status |= static_queue_push(&pbr_queue, &entity);
  return status;
}
void ecs_dispatch(static_queue_t* queue, u32 index, dispatch_t dispatch_type)
{
  entity_t* entity = NULL;
  queue_iter_t iter;
  queue_iter_create(&iter, queue);
  while (queue_iter_valid(&iter) == 0)
  {
    entity = *(entity_t**)queue_iter_value(&iter);
    if (procedures[index] != NULL)
    {
      procedures[index](entity);
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
void ecs_dispatch_gizmo()
{
  ecs_dispatch(&gizmo_queue, queue_idx_gizmo, dispatch_gizmo);
}
void ecs_dispatch_pbr()
{
  ecs_dispatch(&pbr_queue, queue_idx_pbr, dispatch_pbr);
}
void ecs_call_available_procedures(entity_t* entity, dispatch_t dispatch_type)
{
  switch (dispatch_type)
  {
    case dispatch_update:
      if ((entity->proc_mask & event_mask_update) == event_mask_update) ((queue_proc_t)entity->procedures[event_idx_update])(entity);
      break;
    case dispatch_physic:
      if ((entity->proc_mask & event_mask_physic) == event_mask_physic) ((queue_proc_t)entity->procedures[event_idx_physic])(entity);
      break;
    case dispatch_gizmo:
      if ((entity->proc_mask & event_mask_gizmo) == event_mask_gizmo) ((queue_proc_t)entity->procedures[event_idx_gizmo])(entity);
      break;
    case dispatch_pbr:
      if ((entity->proc_mask & event_mask_pbr) == event_mask_pbr) ((queue_proc_t)entity->procedures[event_idx_pbr])(entity);
      break;
  }
}
void ecs_destroy()
{
  static_queue_destroy(&pbr_queue);
  static_queue_destroy(&gizmo_queue);
  static_queue_destroy(&physic_queue);
  static_queue_destroy(&update_queue);
  fwd_list_destroy(&entities);
}