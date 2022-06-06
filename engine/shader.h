#ifndef SHADER_H
#define SHADER_H

#include <core/types.h>

typedef enum
{
  shader_render,
  shader_compute,
} shader_type_t;

typedef struct
{
  shader_type_t type;
  i8 files[3][256];
  u32 pid;
} shader_t;

u8 shader_check_compile_status(u32 shader_id);
u8 shader_check_link_status(u32 program_id);

u8 shader_create(shader_t* shader);
void shader_bind(shader_t* shader);
void shader_uniform_r32(shader_t* shader, i8 const* uniform_name, r32 v);
void shader_uniform_r32m4(shader_t* shader, i8 const* uniform_name, r32m4 m);
void shader_execute(shader_t* shader, u32 x, u32 y, u32 z);
void shader_unbind();
void shader_destroy(shader_t* shader);

#endif