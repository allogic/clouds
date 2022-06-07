#ifndef ECS_H
#define ECS_H

#include <core/types.h>
#include <core/static_queue.h>

#include <components/transform.h>
#include <components/camera.h>
#include <components/mesh.h>
#include <components/rigidbody.h>
#include <components/audio_listener.h>
#include <components/audio_source.h>

#define ECS_NUM_ENTITY_X ((u32)32)
#define ECS_NUM_ENTITY_Y ((u32)32)
#define ECS_NUM_ENTITY_Z ((u32)32)
#define ECS_NUM_ENTITIES ((u32)(ECS_NUM_ENTITY_X * ECS_NUM_ENTITY_Y * ECS_NUM_ENTITY_Z))

#define ECS_UPDATE_QUEUE_SIZE ((u32)32*32*32*2)
#define ECS_PHYSIC_QUEUE_SIZE ((u32)32*32*32*2)
#define ECS_GIZMO_QUEUE_SIZE  ((u32)32*32*32*2)
#define ECS_PBR_QUEUE_SIZE    ((u32)32*32*32*2)

typedef enum
{
  comp_bit_transform      = 0x0000000000000001, comp_idx_transform      = 0,
  comp_bit_camera         = 0x0000000000000002, comp_idx_camera         = 1,
  comp_bit_mesh           = 0x0000000000000004, comp_idx_mesh           = 2,
  comp_bit_rigibody       = 0x0000000000000008, comp_idx_rigidbody      = 3,
  comp_bit_audio_listener = 0x0000000000000010, comp_idx_audio_listener = 4,
  comp_bit_audio_source   = 0x0000000000000020, comp_idx_audio_source   = 5,
} comp_map_t;

#define ECS_TRANSFORM(ENTITY) ((transform_t*)((entity_t*)ENTITY)->components[comp_idx_transform])
#define ECS_CAMERA(ENTITY) ((camera_t*)((entity_t*)ENTITY)->components[comp_idx_camera])
#define ECS_MESH(ENTITY) ((mesh_t*)((entity_t*)ENTITY)->components[comp_idx_mesh])
#define ECS_RIGIDBODY(ENTITY) ((rigidbody_t*)((entity_t*)ENTITY)->components[comp_idx_rigidbody])
#define ECS_AUDIO_LISTENER(ENTITY) ((audio_listener_t*)((entity_t*)ENTITY)->components[comp_idx_audio_listener])
#define ECS_AUDIO_SOURCE(ENTITY) ((audio_source_t*)((entity_t*)ENTITY)->components[comp_idx_audio_source])

typedef enum
{
  proc_bit_update = 0x0000000000000001, proc_idx_update = 0,
  proc_bit_physic = 0x0000000000000002, proc_idx_physic = 1,
  proc_bit_gizmo  = 0x0000000000000004, proc_idx_gizmo  = 2,
  proc_bit_pbr    = 0x0000000000000008, proc_idx_pbr    = 3,
} proc_map_t;

typedef enum
{
  queue_mask_update = comp_bit_transform,                     queue_idx_update = 0,
  queue_mask_physic = comp_bit_transform | comp_bit_rigibody, queue_idx_physic = 1,
  queue_mask_gizmo  = comp_bit_transform,                     queue_idx_gizmo  = 2,
  queue_mask_pbr    = comp_bit_transform | comp_bit_mesh,     queue_idx_pbr    = 3,
} queue_map_t;

typedef enum
{
  event_mask_update = proc_bit_update, event_idx_update = 0,
  event_mask_physic = proc_bit_physic, event_idx_physic = 1,
  event_mask_gizmo  = proc_bit_gizmo,  event_idx_gizmo  = 2,
  event_mask_pbr    = proc_bit_pbr,    event_idx_pbr    = 3,
} event_map_t;

typedef struct
{
  u32 id;
  u64 comp_mask;
  u64 proc_mask;
  void* components[64];
  void* procedures[64];
} entity_t;

typedef void(*queue_proc_t)(entity_t* entity);

typedef enum
{
  dispatch_update, // uncapped
  dispatch_gizmo,  // fixed
  dispatch_pbr,    // fixed
  dispatch_physic, // fixed
} dispatch_t;

u8 ecs_create();
entity_t* ecs_create_entity();
void ecs_erase(entity_t* entity);
transform_t* ecs_attach_transform(entity_t* entity, u8* status);
camera_t* ecs_attach_camera(entity_t* entity, u8* status);
mesh_t* ecs_attach_mesh(entity_t* entity, u8* status);
rigidbody_t* ecs_attach_rigidbody(entity_t* entity, u8* status);
audio_listener_t* ecs_attach_audio_listener(entity_t* entity, u8* status);
audio_source_t* ecs_attach_audio_source(entity_t* entity, u8* status);
u8 ecs_register_static(u32 index, queue_proc_t proc);
u8 ecs_register_dynamic(entity_t* entity, u32 index, u64 bit, queue_proc_t proc);
u8 ecs_update_queues(entity_t* entity);
void ecs_dispatch(static_queue_t* queue, u32 index, dispatch_t dispatch_type);
void ecs_dispatch_update();
void ecs_dispatch_physic();
void ecs_dispatch_gizmo();
void ecs_dispatch_pbr();
void ecs_call_available_procedures(entity_t* entity, dispatch_t dispatch_type);
void ecs_destroy();

#endif