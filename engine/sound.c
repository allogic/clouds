#include <stdio.h>
#include <string.h>

#include <al/al.h>
#include <al/alc.h>

#include <sound.h>

static ALCdevice* device;
static ALCcontext* context;

void sound_queue_proc(entity_t* entity)
{
  transform_t* transform = ECS_TRANSFORM(entity);
  rigidbody_t* rigidbody = ECS_RIGIDBODY(entity);
  audio_listener_t* audio_listener = ECS_AUDIO_LISTENER(entity);
  audio_source_t* audio_source = ECS_AUDIO_SOURCE(entity);
  if (audio_listener != NULL)
  {
    alListener3f(AL_POSITION, TRANSFORM_POSITION(transform)[0], TRANSFORM_POSITION(transform)[1], TRANSFORM_POSITION(transform)[2]);
    if (rigidbody != NULL)
    {
      alListener3f(AL_VELOCITY, rigidbody->position_velocity[0], rigidbody->position_velocity[1], rigidbody->position_velocity[2]);
    }
    r32 orientation[] = { transform->local_front[0], transform->local_front[1], transform->local_front[2], transform->local_up[0], transform->local_up[1], transform->local_up[2] };
    alListenerfv(AL_ORIENTATION, orientation);
  }
  if (audio_source != NULL)
  {
    alSourcef(audio_source->id, AL_PITCH, audio_source->pitch);
    alSourcef(audio_source->id, AL_GAIN, audio_source->gain);
    alSource3f(audio_source->id, AL_POSITION, TRANSFORM_POSITION(transform)[0], TRANSFORM_POSITION(transform)[1], TRANSFORM_POSITION(transform)[2]);
    if (rigidbody != NULL)
    {
      alSource3f(audio_source->id, AL_VELOCITY, rigidbody->position_velocity[0], rigidbody->position_velocity[1], rigidbody->position_velocity[2]);
    }
    alSourcei(audio_source->id, AL_LOOPING, (i32)audio_source->loop);
  }
}

u8 sound_create()
{
  alGetError();
  device = alcOpenDevice(NULL);
  if (device != NULL)
  {
    context = alcCreateContext(device, NULL);
    if (context != NULL)
    {
      if (alcMakeContextCurrent(context) == 1)
      {
        ecs_register_static(queue_idx_sound, sound_queue_proc);
        return 0;
      }
      alcDestroyContext(context);
    }
    alcCloseDevice(device);
  }
  return 1;
}
void sound_step()
{
  ecs_dispatch_sound();
}
void sound_destroy()
{
  alcMakeContextCurrent(NULL);
  if (context != NULL)
  {
    alcDestroyContext(context);
    context = NULL;
  }
  if (device != NULL)
  {
    alcCloseDevice(device);
    device = NULL;
  }
}