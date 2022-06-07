#include <al.h>

#include <components/audio_source.h>

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
void audio_source_update(audio_source_t* audio_source, transform_t* transform, rigidbody_t* rigidbody)
{
  alSourcef(audio_source->id, AL_PITCH, audio_source->pitch);
  alSourcef(audio_source->id, AL_GAIN, audio_source->gain);
  alSource3f(audio_source->id, AL_POSITION, TRANSFORM_POSITION(transform)[0], TRANSFORM_POSITION(transform)[1], TRANSFORM_POSITION(transform)[2]);
  alSource3f(audio_source->id, AL_VELOCITY, rigidbody->position_velocity[0], rigidbody->position_velocity[1], rigidbody->position_velocity[2]);
  alSourcei(audio_source->id, AL_LOOPING, (i32)audio_source->loop);
}
void audio_source_destroy(audio_source_t* audio_source)
{
  alDeleteSources(1, &audio_source->id);
  audio_source->id = 0;
}