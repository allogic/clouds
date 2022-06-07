#ifndef PHYSIC_H
#define PHYSIC_H

#include <core/types.h>

#include <ecs.h>

void physic_queue_proc(entity_t* entity);

u8 physic_create();
void physic_step(r32 steps_size);
void physic_destroy();

#endif