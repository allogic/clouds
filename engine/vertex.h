#ifndef VERTEX_H
#define VERTEX_H

#include <core/types.h>

typedef struct
{
  r32v4 position;
  r32v4 color;
} vertex_line_t;

typedef struct
{
  r32v4 position;
  r32v4 color;
} vertex_text_t;

typedef struct
{
  r32v4 position;
  r32v4 normal;
  r32v4 color;
  r32v2 uv;
} vertex_pbr_t;

#endif