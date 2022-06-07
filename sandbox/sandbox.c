#include <stdio.h>

#include <gizmo.h>

#include <entities/world.h>
#include <entities/player.h>

#include <sandbox.h>

r32v2 window_size = { 1280, 720 };

r32 ticks_render = 1.0f / 60;
r32 ticks_physic = 1.0f / 60;

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