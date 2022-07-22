#include <core/file_system.h>

#include <profiler.h>

#include <gizmo.h>
#include <assets.h>

#include <entities/world.h>
#include <entities/player.h>

#include <sandbox.h>

r32v2 window_size = { 1280, 720 };

r32 ticks_render = 1.0f / 60;
r32 ticks_physic = 1.0f / 60;
r32 ticks_sound = 1.0f / 60;

SOUND_TABLE_BEGIN
SOUND_TABLE_RECORD(ENGINE_ROOT_DIR "assets\\sounds\\spaceship_hum.wav")
SOUND_TABLE_RECORD(ENGINE_ROOT_DIR "assets\\sounds\\spaceship_vibrato.wav")
SOUND_TABLE_END

MODEL_TABLE_BEGIN
MODEL_TABLE_RECORD(ENGINE_ROOT_DIR "assets\\models\\atlas_heavy_fighter_hull.fbx")
MODEL_TABLE_END

TEXTURE_TABLE_BEGIN
TEXTURE_TABLE_RECORD(ENGINE_ROOT_DIR "assets\\textures\\atlas_heavy_fighter_normal.png")
TEXTURE_TABLE_RECORD(ENGINE_ROOT_DIR "assets\\textures\\atlas_heavy_fighter_ao.png")
TEXTURE_TABLE_RECORD(ENGINE_ROOT_DIR "assets\\textures\\atlas_heavy_fighter_white_albedo.png")
TEXTURE_TABLE_RECORD(ENGINE_ROOT_DIR "assets\\textures\\atlas_heavy_fighter_white_albedo_ao.png")
TEXTURE_TABLE_END

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif