#ifndef EVENTS_H
#define EVENTS_H

#include <core/types.h>

typedef enum
{
  event_none,
  event_down,
  event_held,
  event_up,
} event_state_t;

typedef struct
{
  event_state_t current;
  event_state_t previous;
} event_t;

u8 key_down(u32 key);
u8 key_held(u32 key);
u8 key_up(u32 key);

u8 mouse_down(u32 key);
u8 mouse_held(u32 key);
u8 mouse_up(u32 key);

void events_poll(GLFWwindow* window);

#endif