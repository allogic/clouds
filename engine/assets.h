#ifndef ASSETS_H
#define ASSETS_H

#include <core/core.h>
#include <core/types.h>

typedef struct
{
  i8 file[256];
  u32 id;
} sound_asset_t;

typedef struct
{
  i8 file[256];
} mesh_asset_t;

#define SOUND_TABLE_SIZE 256
#define SOUND_TABLE_BEGIN sound_asset_t table_sound[SOUND_TABLE_SIZE] = {
#define SOUND_TABLE_EMPTY 0,
#define SOUND_TABLE_RECORD(FILE) { FILE },
#define SOUND_TABLE_END };

#define MESH_TABLE_SIZE 256
#define MESH_TABLE_BEGIN mesh_asset_t table_mesh[MESH_TABLE_SIZE] = {
#define MESH_TABLE_EMPTY 0,
#define MESH_TABLE_RECORD(FILE) { FILE },
#define MESH_TABLE_END };

u8 assets_create();
u8 asset_load_sound();
u8 asset_load_mesh();
sound_asset_t* asset_get_sound(u32 index);
mesh_asset_t* asset_get_mesh(u32 index);
void assets_destroy();

#endif