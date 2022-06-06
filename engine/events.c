#include <glfw3.h>

#include <events.h>

static event_t mouse_key_states[GLFW_MOUSE_BUTTON_LAST];
static event_t keyboard_key_states[GLFW_KEY_LAST];

u8 key_down(u32 key)
{
  return keyboard_key_states[key].current == event_down;
}
u8 key_held(u32 key)
{
  return keyboard_key_states[key].current == event_held;
}
u8 key_up(u32 key)
{
  return keyboard_key_states[key].current == event_up;
}

u8 mouse_down(u32 key)
{
  return mouse_key_states[key].current == event_down;
}
u8 mouse_held(u32 key)
{
  return mouse_key_states[key].current == event_held;
}
u8 mouse_up(u32 key)
{
  return mouse_key_states[key].current == event_up;
}

void events_poll(GLFWwindow* window)
{
  glfwPollEvents();
  for (u32 i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++)
  {
    i32 action = glfwGetMouseButton(window, (i32)i);
    mouse_key_states[i].previous = mouse_key_states[i].current;
    if (action == GLFW_PRESS)
    {
      if (mouse_key_states[i].current != event_down && mouse_key_states[i].previous != event_held)
      {
        mouse_key_states[i].current = event_down;
      }
      else
      {
        mouse_key_states[i].current = event_held;
      }
    }
    if (action == GLFW_RELEASE)
    {
      if (mouse_key_states[i].current != event_up && mouse_key_states[i].previous == event_held)
      {
        mouse_key_states[i].current = event_up;
      }
      else
      {
        mouse_key_states[i].current = event_none;
      }
    }
  }
  for (u32 i = GLFW_KEY_SPACE; i < GLFW_KEY_LAST; i++)
  {
    i32 action = glfwGetKey(window, (i32)i);
    keyboard_key_states[i].previous = keyboard_key_states[i].current;
    if (action == GLFW_PRESS)
    {
      if (keyboard_key_states[i].current != event_down && keyboard_key_states[i].previous != event_held)
      {
        keyboard_key_states[i].current = event_down;
      }
      else
      {
        keyboard_key_states[i].current = event_held;
      }
    }
    if (action == GLFW_RELEASE)
    {
      if (keyboard_key_states[i].current != event_up && keyboard_key_states[i].previous == event_held)
      {
        keyboard_key_states[i].current = event_up;
      }
      else
      {
        keyboard_key_states[i].current = event_none;
      }
    }
  }
}