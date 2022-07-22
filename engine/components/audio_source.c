#include <al/al.h>

#include <components/audio_source.h>

#ifdef __cplusplus
extern "C" {
#endif

  u8 audio_source_create(audio_source_t* audio_source)
  {
    audio_source->pitch = 1.0f;
    audio_source->gain = 1.0f;
    audio_source->loop = 1;
    alGenSources(1, &audio_source->id);
    if (audio_source->id != 0)
    {
      return 0;
    }
    return 1;
  }
  u8 audio_source_from(audio_source_t* audio_source, sound_t* sound)
  {
    i32 source_state = 0;
    alGetSourcei(audio_source->id, AL_SOURCE_STATE, &source_state);
    if (source_state != AL_PLAYING)
    {
      alSourcei(audio_source->id, AL_BUFFER, sound->id);
      return 0;
    }
    return 1;
  }
  u8 audio_source_play(audio_source_t* audio_source, r32 gain)
  {
    i32 source_state = 0;
    alGetSourcei(audio_source->id, AL_SOURCE_STATE, &source_state);
    if (source_state != AL_PLAYING)
    {
      alSourcef(audio_source->id, AL_GAIN, gain);
      alSourcePlay(audio_source->id);
      return 0;
    }
    return 1;
  }
  u8 audio_source_stop(audio_source_t* audio_source)
  {
    i32 source_state = 0;
    alGetSourcei(audio_source->id, AL_SOURCE_STATE, &source_state);
    if (source_state == AL_PLAYING)
    {
      alSourceStop(audio_source->id);
      return 0;
    }
    return 1;
  }
  u8 audio_source_unbind(audio_source_t* audio_source)
  {
    i32 source_state = 0;
    alGetSourcei(audio_source->id, AL_SOURCE_STATE, &source_state);
    if (source_state != AL_PLAYING)
    {
      alSourcei(audio_source->id, AL_BUFFER, 0);
      return 0;
    }
    return 1;
  }
  u8 audio_source_destroy(audio_source_t* audio_source)
  {
    i32 source_state = 0;
    alGetSourcei(audio_source->id, AL_SOURCE_STATE, &source_state);
    if (source_state != AL_PLAYING)
    {
      alDeleteSources(1, &audio_source->id);
      audio_source->id = 0;
      return 0;
    }
    return 1;
  }

#ifdef __cplusplus
}
#endif