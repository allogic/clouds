#ifndef SOUND_H
#define SOUND_H

#include <core/types.h>

#include <ecs.h>

void sound_queue_proc(entity_t* entity);

u8 sound_create();
void sound_step();
void sound_destroy();

#endif