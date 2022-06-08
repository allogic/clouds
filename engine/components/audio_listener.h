#ifndef AUDIO_LISTENER_H
#define AUDIO_LISTENER_H

#include <core/types.h>

typedef struct
{
  u32 reserved;
} audio_listener_t;

u8 audio_listener_create(audio_listener_t* audio_listener);

#endif