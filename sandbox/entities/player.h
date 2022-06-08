#ifndef PLAYER_H
#define PLAYER_H

#include <core/types.h>

#include <ecs.h>

void update_player_proc(entity_t* entity);
void gizmo_player_proc(entity_t* entity);
void physic_thruster_proc(entity_t* entity);

u8 player_create();
void player_break(rigidbody_t* rigidbody);
void player_boost(transform_t* transform, rigidbody_t* rigidbody);
void player_drift(transform_t* transform, rigidbody_t* rigidbody);
void player_destroy();

#endif