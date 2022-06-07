#ifndef UPDATE_H
#define UPDATE_H

#include <core/types.h>

#include <ecs.h>

void update_queue_proc(entity_t* entity);

u8 update_create();
void update_step();
void update_destroy();

#endif