#ifndef PBR_H
#define PBR_H

#include <core/types.h>

#include <ecs.h>

void render_queue_proc(entity_t* entity);

u8 pbr_create();
void pbr_render();
void pbr_destroy();

#endif