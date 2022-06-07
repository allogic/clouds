#include <glfw3.h>
#include <cglm.h>

#include <gizmo.h>
#include <constants.h>
#include <events.h>
#include <vertex.h>

#include <entities/player.h>
#include <entities/world.h>

#define BREAK_AMOUNT 0.00005f
#define BOOST_AMOUNT 0.001f
#define DRIFT_AMOUNT 0.0002f

extern r32v2 window_size;
extern r32v2 mouse_position;
extern r32 delta_time;

entity_t* player = NULL;

static transform_t* transform = NULL;
static camera_t* camera = NULL;
static rigidbody_t* rigidbody = NULL;
static mesh_t* mesh = NULL;
static audio_listener_t* audio_listener = NULL;

void update_player_proc(entity_t* entity)
{
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
  if (drifting) player_drift();
  if (breaking) player_break();
  if (boosting) player_boost();

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
void gizmo_player_proc(entity_t* entity)
{
  //r32v3 a = { TRANSFORM_POSITION(transform)[0], TRANSFORM_POSITION(transform)[1], TRANSFORM_POSITION(transform)[2] };
  //r32v3 b = { TRANSFORM_POSITION(transform)[0] + rigidbody->position_velocity[0], TRANSFORM_POSITION(transform)[1] + rigidbody->position_velocity[1], TRANSFORM_POSITION(transform)[2] + rigidbody->position_velocity[2] };
  //gizmo_push_line(a, b, yellow);
  gizmo_push_box(TRANSFORM_POSITION(transform), TRANSFORM_SCALE(transform), red);
}

u8 player_create()
{
  u8 status = 0;
  player = ecs_create_entity();
  transform = ecs_attach_transform(player, &status);
  camera = ecs_attach_camera(player, &status);
  rigidbody = ecs_attach_rigidbody(player, &status);
  mesh = ecs_attach_mesh(player, &status);
  audio_listener = ecs_attach_audio_listener(player, &status);
  status |= mesh_push(mesh, 3, sizeof(vertex_pbr_t), 3, sizeof(u32));
  status |= mesh_select_layout(mesh, 0, mesh_pbr);
  status |= ecs_register_dynamic(player, proc_idx_update, proc_bit_update, update_player_proc);
  status |= ecs_register_dynamic(player, proc_idx_gizmo, proc_bit_gizmo, gizmo_player_proc);
  status |= ecs_update_queues(player);
  return status;
}
void player_break()
{
  static r32v3 accel_break;
  glm_vec3_scale(rigidbody->position_velocity, -BREAK_AMOUNT, accel_break);
  rigidbody_add_velocity_position(rigidbody, accel_break);
}
void player_boost()
{
  static r32v3 accel_boost;
  glm_vec3_scale(transform->local_front, BOOST_AMOUNT, accel_boost);
  rigidbody_add_velocity_position(rigidbody, accel_boost);
}
void player_drift()
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