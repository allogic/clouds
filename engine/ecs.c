#include <string.h>

#include <core/fwd_list.h>
#include <core/queue_iterator.h>

#include <ecs.h>
#include <physic.h>
#include <sbo.h>

static u32 entity_id = 0;
static u32 transform_id = 0;
static u32 rigidbody_id = 0;

fwd_list_t entities;

static static_queue_t queue_update;
static static_queue_t queue_physic;
static static_queue_t queue_gizmo;
static static_queue_t queue_pbr;
static static_queue_t queue_sound;

static queue_proc_t procedures[64];

extern sbo_t transforms;
extern sbo_t rigidbodies;

#ifdef __cplusplus
extern "C" {
#endif

  u8 ecs_create()
  {
    fwd_list_create(&entities);
    static_queue_create(&queue_update, ECS_UPDATE_QUEUE_SIZE, sizeof(entity_t*));
    static_queue_create(&queue_physic, ECS_PHYSIC_QUEUE_SIZE, sizeof(entity_t*));
    static_queue_create(&queue_gizmo, ECS_GIZMO_QUEUE_SIZE, sizeof(entity_t*));
    static_queue_create(&queue_pbr, ECS_PBR_QUEUE_SIZE, sizeof(entity_t*));
    static_queue_create(&queue_sound, ECS_SOUND_QUEUE_SIZE, sizeof(entity_t*));
    return 0;
  }
  entity_t* ecs_create_entity()
  {
    entity_t* entity = fwd_list_push(&entities, NULL, sizeof(entity_t));
    if (entity != NULL)
    {
      entity->id = entity_id++;
    }
    return entity;
  }
  void ecs_erase(entity_t* entity)
  {
    fwd_list_erase(&entities, entity);
  }
  transform_t* ecs_attach_transform(entity_t* entity, transform_t* parent, u8* status)
  {
    transform_t* transform = NULL;
    entity->components[comp_idx_transform] = &((transform_t*)transforms.data)[transform_id];
    entity->comp_mask |= comp_bit_transform;
    transform = ECS_TRANSFORM(entity);
    *status |= transform_create(transform);
    transform->transform_id = transform_id;
    if (parent != NULL)
    {
      transform->transform_parent_id = parent->transform_id;
    }
    transform_id++;
    return transform;
  }
  camera_t* ecs_attach_camera(entity_t* entity, u8* status)
  {
    camera_t* camera = NULL;
    entity->components[comp_idx_camera] = calloc(1, sizeof(camera_t));
    entity->comp_mask |= comp_bit_camera;
    camera = ECS_CAMERA(entity);
    *status |= camera_create(camera);
    return camera;
  }
  mesh_t* ecs_attach_mesh(entity_t* entity, u8* status)
  {
    mesh_t* mesh = NULL;
    entity->components[comp_idx_mesh] = calloc(1, sizeof(mesh_t));
    entity->comp_mask |= comp_bit_mesh;
    mesh = ECS_MESH(entity);
    *status |= mesh_create(mesh);
    return mesh;
  }
  rigidbody_t* ecs_attach_rigidbody(entity_t* entity, u8* status)
  {
    rigidbody_t* rigidbody = NULL;
    ECS_TRANSFORM(entity)->rigidbody_id = rigidbody_id;
    entity->components[comp_idx_rigidbody] = &((rigidbody_t*)rigidbodies.data)[rigidbody_id];
    entity->comp_mask |= comp_bit_rigibody;
    rigidbody = ECS_RIGIDBODY(entity);
    *status |= rigidbody_create(rigidbody);
    rigidbody->rigidbody_id = rigidbody_id;
    ECS_TRANSFORM(entity)->mask |= transform_dynamic;
    rigidbody_id++;
    return rigidbody;
  }
  audio_listener_t* ecs_attach_audio_listener(entity_t* entity, u8* status)
  {
    audio_listener_t* audio_listener = NULL;
    entity->components[comp_idx_audio_listener] = calloc(1, sizeof(audio_listener_t));
    entity->comp_mask |= comp_bit_audio_listener;
    audio_listener = ECS_AUDIO_LISTENER(entity);
    *status |= audio_listener_create(audio_listener);
    return audio_listener;
  }
  audio_source_t* ecs_attach_audio_source(entity_t* entity, u8* status)
  {
    audio_source_t* audio_source = NULL;
    entity->components[comp_idx_audio_source] = calloc(1, sizeof(audio_source_t));
    entity->comp_mask |= comp_bit_audio_source;
    audio_source = ECS_AUDIO_SOURCE(entity);
    *status |= audio_source_create(audio_source);
    return audio_source;
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
    if ((entity->comp_mask & queue_mask_update) == queue_mask_update) status |= static_queue_push(&queue_update, &entity);
    if ((entity->comp_mask & queue_mask_physic) == queue_mask_physic) status |= static_queue_push(&queue_physic, &entity);
    if ((entity->comp_mask & queue_mask_gizmo) == queue_mask_gizmo) status |= static_queue_push(&queue_gizmo, &entity);
    if ((entity->comp_mask & queue_mask_pbr) == queue_mask_pbr) status |= static_queue_push(&queue_pbr, &entity);
    if ((entity->comp_mask & queue_mask_sound) == queue_mask_sound) status |= static_queue_push(&queue_sound, &entity);
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
    ecs_dispatch(&queue_update, queue_idx_update, dispatch_update);
  }
  void ecs_dispatch_physic()
  {
    ecs_dispatch(&queue_physic, queue_idx_physic, dispatch_physic);
  }
  void ecs_dispatch_gizmo()
  {
    ecs_dispatch(&queue_gizmo, queue_idx_gizmo, dispatch_gizmo);
  }
  void ecs_dispatch_pbr()
  {
    ecs_dispatch(&queue_pbr, queue_idx_pbr, dispatch_pbr);
  }
  void ecs_dispatch_sound()
  {
    ecs_dispatch(&queue_sound, queue_idx_sound, dispatch_sound);
  }
  void ecs_call_available_procedures(entity_t* entity, dispatch_t dispatch_type)
  {
    switch (dispatch_type)
    {
    case dispatch_update:
      if ((entity->proc_mask & event_mask_update) == event_mask_update) ((queue_proc_t)entity->procedures[event_idx_update])(entity);
      if ((entity->proc_mask & event_mask_ui) == event_mask_ui) ((queue_proc_t)entity->procedures[event_idx_ui])(entity);
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
    static_queue_destroy(&queue_pbr);
    static_queue_destroy(&queue_gizmo);
    static_queue_destroy(&queue_physic);
    static_queue_destroy(&queue_update);
    fwd_list_destroy(&entities);
  }

#ifdef __cplusplus
}
#endif