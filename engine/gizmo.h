#ifndef GIZMO_H
#define GIZMO_H

#include <core/types.h>

#include <ecs.h>

#define GIZMO_NUM_VERTEX_LINE ((u32)32*32*32*32)
#define GIZMO_NUM_VERTEX_TEXT ((u32)32*32*32*32)

void gizmo_queue_proc(entity_t* entity);

u8 gizmo_create();
void gizmo_push_line(r32v3 a, r32v3 b, r32v4 c);
void gizmo_push_box(r32v3 p, r32v3 s, r32v4 c);
void gizmo_push_sphere(r32v3 p, r32 radius, u32 segments, r32v4 c);
void gizmo_push_text(r32v3 p, r32v3 s, i8 const* str, r32v4 c);
void gizmo_render();
void gizmo_destroy();

#endif