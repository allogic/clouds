#ifndef WORLD_H
#define WORLD_H

#include <core/types.h>

#include <ecs.h>

#define CHUNK_NUM_ROOTS ((u32)32)
#define CHUNK_NUM_LEAFS ((u32)1)

#define CHUNK_SIZE_X ((u32)32)
#define CHUNK_SIZE_Y ((u32)32)
#define CHUNK_SIZE_Z ((u32)32)

typedef struct
{
  r32v3 position;
  r32v3 size;
} chunk_t;

#ifdef __cplusplus
extern "C" {
#endif

  u8 world_create();
  void world_build();
  void world_destroy();

#ifdef __cplusplus
}
#endif

#endif