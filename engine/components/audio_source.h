#ifndef AUDIO_SOURCE_H
#define AUDIO_SOURCE_H

#include <core/types.h>

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
void audio_source_update(audio_source_t* audio_source, transform_t* transform, rigidbody_t* rigidbody);
void audio_source_destroy(audio_source_t* audio_source);

#endif