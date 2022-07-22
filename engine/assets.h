#ifndef ASSETS_H
#define ASSETS_H

#include <core/core.h>
#include <core/types.h>
#include <core/fwd_list.h>

typedef struct
{
  u32 id;
} sound_t;
typedef struct
{
  i8 file[256];
  sound_t sound;
} sound_asset_t;

typedef struct
{
  fwd_list_t vertices;
  fwd_list_t elements;
} model_t;
typedef struct
{
  i8 file[256];
  fwd_list_t models;
} model_asset_t;

typedef struct
{
  u32 dummy;
} texture_t;
typedef struct
{
  i8 file[256];
  texture_t texture;
} texture_asset_t;

#define SOUND_TABLE_SIZE 256
#define MODEL_TABLE_SIZE 256
#define TEXTURE_TABLE_SIZE 256

#define SOUND_TABLE_BEGIN sound_asset_t table_sound[SOUND_TABLE_SIZE] = {
#define SOUND_TABLE_EMPTY 0,
#define SOUND_TABLE_RECORD(FILE) { FILE },
#define SOUND_TABLE_END };

#define MODEL_TABLE_BEGIN model_asset_t table_model[MODEL_TABLE_SIZE] = {
#define MODEL_TABLE_EMPTY 0,
#define MODEL_TABLE_RECORD(FILE) { FILE },
#define MODEL_TABLE_END };

#define TEXTURE_TABLE_BEGIN texture_asset_t table_texture[TEXTURE_TABLE_SIZE] = {
#define TEXTURE_TABLE_EMPTY 0,
#define TEXTURE_TABLE_RECORD(FILE) { FILE },
#define TEXTURE_TABLE_END };

#ifdef __cplusplus
extern "C" {
#endif

  u8 assets_create();
  u8 assets_load_sound();
  u8 assets_load_model();
  u8 assets_load_texture();
  sound_asset_t* assets_get_sound(u32 index);
  model_asset_t* assets_get_model(u32 index);
  texture_asset_t* assets_get_texture(u32 index);
  void assets_destroy();

#ifdef __cplusplus
}
#endif

#endif