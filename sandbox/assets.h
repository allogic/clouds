#ifndef ASSETS_H
#define ASSETS_H

#include <asset_db.h>
#include <constants.h>

ASSET_TABLE_BEGIN()
ASSET_TABLE_RECORD(asset_audio, ENGINE_ROOT_DIR "assets\\audio\\spaceship_hum.wav")
ASSET_TABLE_RECORD(asset_audio, ENGINE_ROOT_DIR "assets\\audio\\spaceship_vibrato.wav")
ASSET_TABLE_END()

#endif