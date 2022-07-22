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

#ifdef __cplusplus
extern "C" {
#endif

  u8 audio_source_create(audio_source_t* audio_source);
  u8 audio_source_from(audio_source_t* audio_source, sound_t* sound);
  u8 audio_source_stop(audio_source_t* audio_source);
  u8 audio_source_play(audio_source_t* audio_source, r32 gain);
  u8 audio_source_unbind(audio_source_t* audio_source);
  u8 audio_source_destroy(audio_source_t* audio_source);

#ifdef __cplusplus
}
#endif

#endif