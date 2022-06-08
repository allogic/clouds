#ifndef AUDIO_SOURCE_H
#define AUDIO_SOURCE_H

#include <core/types.h>

#include <assets.h>

#include <components/transform.h>
#include <components/rigidbody.h>

typedef struct
{
  u32 id;
  r32 pitch;
  r32 gain;
  u8 loop;
} audio_source_t;

u8 audio_source_create(audio_source_t* audio_source);
u8 audio_source_bind(audio_source_t* audio_source, sound_asset_t* sound_asset);
u8 audio_source_stop(audio_source_t* audio_source);
u8 audio_source_play(audio_source_t* audio_source);
u8 audio_source_unbind(audio_source_t* audio_source);
u8 audio_source_destroy(audio_source_t* audio_source);

#endif