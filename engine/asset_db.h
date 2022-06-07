#ifndef ASSET_DB_H
#define ASSET_DB_H

#include <core/types.h>

typedef enum
{
  asset_audio = 0,
  asset_mesh  = 1,
} asset_type_t;

typedef struct
{
  asset_type_t info;
  i8 file[256];
  void* data;
} asset_t;

#define ASSET_TABLE_BEGIN              asset_t assets[] = {
#define ASSET_TABLE_RECORD(INFO, FILE)   { INFO, FILE, NULL },
#define ASSET_TABLE_END                };

u8 asset_db_create();
void asset_db_destroy();

#endif