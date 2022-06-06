#ifndef RENDERER_H
#define RENDERER_H

#include <core/types.h>

#include <ecs.h>

void render_queue_proc(entity_t* entity);

u8 renderer_create();
void renderer_render(r32 delta_time);
void renderer_destroy();

#endif
