#include <stdio.h>

#include <gizmo.h>
#include <assets.h>
#include <constants.h>

#include <entities/world.h>
#include <entities/player.h>

#include <sandbox.h>

r32v2 window_size = { 1280, 720 };

r32 ticks_render = 1.0f / 60;
r32 ticks_physic = 1.0f / 60;
r32 ticks_sound = 1.0f / 60;

SOUND_TABLE_BEGIN
SOUND_TABLE_RECORD(ENGINE_ROOT_DIR "assets\\audio\\spaceship_hum.wav")
SOUND_TABLE_RECORD(ENGINE_ROOT_DIR "assets\\audio\\spaceship_vibrato.wav")
SOUND_TABLE_END

MESH_TABLE_BEGIN
MESH_TABLE_EMPTY
MESH_TABLE_END

u8 sandbox_create()
{
  u8 status = 0;
  status |= world_create();
  status |= player_create();
  //world_build();
  return status;
}
void sandbox_destroy()
{
  player_destroy();
  world_destroy();
}