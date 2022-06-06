#include <al.h>
#include <alc.h>

#include <sound.h>

static ALCdevice* device;
static ALCcontext* context;

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
        return 0;
      }
      alcDestroyContext(context);
    }
    alcCloseDevice(device);
  }
  return 1;
}
void sound_update()
{

}
void sound_destroy()
{
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