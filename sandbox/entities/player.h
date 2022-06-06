#ifndef PLAYER_H
#define PLAYER_H

#include <core/types.h>

#include <components/transform.h>
#include <components/camera.h>
#include <components/rigidbody.h>
#include <components/mesh.h>

void update_player_proc(entity_t* entity);
void gizmo_player_proc(entity_t* entity);

u8 player_create();
void player_break();
void player_boost();
void player_drift();
void player_destroy();

#endif