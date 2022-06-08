#include <glfw/glfw3.h>
#include <cglm/cglm.h>

#include <assets.h>
#include <gizmo.h>
#include <constants.h>
#include <events.h>
#include <vertex.h>

#include <entities/player.h>
#include <entities/world.h>

#define BREAK_AMOUNT 0.00005f
#define BOOST_AMOUNT 0.0002f
#define DRIFT_AMOUNT 0.0002f

extern r32v2 window_size;
extern r32v2 mouse_position;
extern r32 delta_time;

entity_t* player = NULL;
entity_t* thruster = NULL;

void update_player_proc(entity_t* entity)
{
  transform_t* transform = ECS_TRANSFORM(player);
  camera_t* camera = ECS_CAMERA(player);
  rigidbody_t* rigidbody = ECS_RIGIDBODY(player);

  // Handle position
  static r32v3 accel_right, accel_up, accel_front;
  glm_vec3_scale(transform->local_right, 0.0001f, accel_right);
  glm_vec3_scale(transform->local_up, 0.0001f, accel_up);
  glm_vec3_scale(transform->local_front, 0.0001f, accel_front);
  if (key_held(GLFW_KEY_A)) rigidbody_add_velocity_position(rigidbody, accel_right);
  if (key_held(GLFW_KEY_D)) rigidbody_sub_velocity_position(rigidbody, accel_right);
  if (key_held(GLFW_KEY_S)) rigidbody_sub_velocity_position(rigidbody, accel_front);
  if (key_held(GLFW_KEY_W)) rigidbody_add_velocity_position(rigidbody, accel_front);

  // Handle states
  u8 drifting = key_held(GLFW_KEY_LEFT_SHIFT) && key_held(GLFW_KEY_SPACE) && (glm_vec3_distance(zero, rigidbody->position_velocity) > 2.0f);
  u8 breaking = key_held(GLFW_KEY_LEFT_CONTROL) && (drifting == 0);
  u8 boosting = key_held(GLFW_KEY_LEFT_SHIFT) && (drifting == 0) && (breaking == 0);
  if (drifting) player_drift(transform, rigidbody);
  if (breaking) player_break(rigidbody);
  if (boosting) player_boost(transform, rigidbody);

  // Handle mouse
  static r32v2 prev_mouse_position, delta_mouse_position;
  if (mouse_down(GLFW_MOUSE_BUTTON_RIGHT))
  {
    prev_mouse_position[0] = mouse_position[0];
    prev_mouse_position[1] = mouse_position[1];
  }
  if (mouse_held(GLFW_MOUSE_BUTTON_RIGHT))
  {
    glm_vec2_sub(mouse_position, prev_mouse_position, delta_mouse_position);
    r32 distance = glm_vec2_distance(prev_mouse_position, delta_mouse_position) * 0.00005f;
    glm_vec2_scale(delta_mouse_position, distance, delta_mouse_position);
    rigidbody_sub_velocity_yaw(rigidbody, -delta_mouse_position[0] * 0.00001f);
    rigidbody_add_velocity_pitch(rigidbody, -delta_mouse_position[1] * 0.000006f);
  }

  // Handle roll
  if (key_held(GLFW_KEY_Q)) rigidbody_add_velocity_roll(rigidbody, 0.00015f);
  if (key_held(GLFW_KEY_E)) rigidbody_sub_velocity_roll(rigidbody, 0.00015f);

  // Clamp rotation
  //glm_vec3_clamp(TRANSFORM_ROTATION(transform), -180.0f, 180.0f);

  // Clamp velocity
  glm_vec3_clamp(rigidbody->position_velocity, -100.0f, 100.0f);
  glm_vec3_clamp(rigidbody->rotation_velocity, -2.0f, 2.0f);

  // Compute projection and view matrix
  glm_perspective(camera->fov, camera->aspect, camera->near, camera->far, camera->projection);
  glm_look(TRANSFORM_POSITION(transform), transform->local_front, transform->local_up, camera->view);
}
void physic_thruster_proc(entity_t* entity)
{
  transform_t* transform = ECS_TRANSFORM(player);
  rigidbody_t* rigidbody = ECS_RIGIDBODY(player);
  audio_source_t* audio_source = ECS_AUDIO_SOURCE(thruster);

  // update pitch
  static r32v3 prev_position;
  r32 distance = glm_vec3_distance(TRANSFORM_POSITION(transform), prev_position);
  prev_position[0] = TRANSFORM_POSITION(transform)[0];
  prev_position[1] = TRANSFORM_POSITION(transform)[1];
  prev_position[2] = TRANSFORM_POSITION(transform)[2];
  r32 pitch = 0.65f + VALUE_REMAP(distance, 0.0f, 20.0f, 0.0f, 2.5f);
  audio_source->pitch = pitch;
}
void gizmo_player_proc(entity_t* entity)
{
  transform_t* transform = ECS_TRANSFORM(entity);
  gizmo_push_box(TRANSFORM_POSITION(transform), TRANSFORM_SCALE(transform), red);
}
void gizmo_thruster_proc(entity_t* entity)
{
  transform_t* transform = ECS_TRANSFORM(entity);
  gizmo_push_box(TRANSFORM_POSITION(transform), TRANSFORM_SCALE(transform), green);
}

u8 player_create()
{
  u8 status = 0;

  transform_t* transform = NULL;
  camera_t* camera = NULL;
  rigidbody_t* rigidbody = NULL;
  mesh_t* mesh = NULL;
  audio_listener_t* audio_listener = NULL;
  audio_source_t* audio_source = NULL;

  // Create player
  player = ecs_create_entity();
  transform = ecs_attach_transform(player, NULL, &status);
  camera = ecs_attach_camera(player, &status);
  rigidbody = ecs_attach_rigidbody(player, &status);
  mesh = ecs_attach_mesh(player, &status);
  audio_listener = ecs_attach_audio_listener(player, &status);
  audio_source = ecs_attach_audio_source(player, &status);
  status |= mesh_push(mesh, 3, sizeof(vertex_pbr_t), 3, sizeof(u32));
  status |= mesh_select_layout(mesh, 0, mesh_pbr);
  status |= audio_source_bind(audio_source, asset_get_sound(0)); // 0 = spaceship hum
  audio_source->gain = 0.35f;
  status |= audio_source_play(audio_source);
  status |= ecs_register_dynamic(player, proc_idx_update, proc_bit_update, update_player_proc);
  status |= ecs_register_dynamic(player, proc_idx_gizmo, proc_bit_gizmo, gizmo_player_proc);
  status |= ecs_update_queues(player);

  // Create thruster
  thruster = ecs_create_entity();
  transform = ecs_attach_transform(thruster, transform, &status);
  rigidbody = ecs_attach_rigidbody(thruster, &status);
  audio_source = ecs_attach_audio_source(thruster, &status);
  status |= audio_source_bind(audio_source, asset_get_sound(1)); // 1 = spaceship vibrato
  audio_source->gain = 0.6f;
  status |= audio_source_play(audio_source);
  status |= ecs_register_dynamic(thruster, proc_idx_physic, proc_bit_physic, physic_thruster_proc);
  status |= ecs_register_dynamic(thruster, proc_idx_gizmo, proc_bit_gizmo, gizmo_thruster_proc);
  status |= ecs_update_queues(thruster);

  return status;
}
void player_break(rigidbody_t* rigidbody)
{
  static r32v3 accel_break;
  glm_vec3_scale(rigidbody->position_velocity, -BREAK_AMOUNT, accel_break);
  rigidbody_add_velocity_position(rigidbody, accel_break);
}
void player_boost(transform_t* transform, rigidbody_t* rigidbody)
{
  static r32v3 accel_boost;
  glm_vec3_scale(transform->local_front, BOOST_AMOUNT, accel_boost);
  rigidbody_add_velocity_position(rigidbody, accel_boost);
}
void player_drift(transform_t* transform, rigidbody_t* rigidbody)
{  
  r32v3 pitch = { TRANSFORM_ROTATION(transform)[0], 0.0f, 0.0f };
  r32v3 yaw = { 0.0f, TRANSFORM_ROTATION(transform)[1], 0.0f };
  r32v3 roll = { 0.0f, 0.0f, TRANSFORM_ROTATION(transform)[2] };

  r32v3 velpitch = { rigidbody->rotation_velocity[0], 0.0f, 0.0f };
  r32v3 velyaw = { 0.0f, rigidbody->rotation_velocity[1], 0.0f };
  r32v3 velroll = { 0.0f, 0.0f, rigidbody->rotation_velocity[2] };

  r32 angleX = glm_dot(yaw, velyaw) * 100.0f;
  r32 angleY = glm_dot(pitch, velpitch) * 100.0f;

  glm_vec3_rotate(rigidbody->position_velocity, angleX, transform->local_right);
  glm_vec3_rotate(rigidbody->position_velocity, angleY, transform->local_up);

  //glm_vec3_scale(transform->local_right, DRIFT_AMOUNT, escape_dir);
  //rigidbody_add_velocity_position(rigidbody, escape_dir);
}
void player_destroy()
{

}