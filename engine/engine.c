#include <stdio.h>
#include <stdlib.h>

#include <glad.h>
#include <glfw3.h>

#include <core/types.h>

#include <ecs.h>
#include <update.h>
#include <renderer.h>
#include <physic.h>
#include <events.h>
#include <asset_db.h>
#include <sound.h>

#include <sandbox.h>

extern r32v2 window_size;
r32v2 mouse_position;

extern r32 ticks_render;
extern r32 ticks_physic;

static GLFWwindow* window = NULL;

static r32 time = 0.0f;
r32 delta_time = 0.0f;
static r32 prev_time = 0.0f;
static r32 prev_render_time = 0.0f;
static r32 prev_physic_time = 0.0f;
static r32 prev_fps_time = 0.0f;

static u32 fps_count = 0;
static i8 fps_title[8];

static u8 status = 0;

extern entity_t* player;

static void glfw_debug_proc(i32 error, i8 const* msg)
{
  printf(msg);
}
static void glfw_close_proc(GLFWwindow* window)
{
  status = 1;
}
static void glfw_resize_proc(GLFWwindow* window, i32 width, i32 height)
{
  window_size[0] = (r32)width;
  window_size[1] = (r32)height;
  if (player != NULL)
  {
    ECS_CAMERA(player)->aspect = (r32)width / (r32)height;
  }
  glViewport(0, 0, (u32)width, (u32)height);
}
static void glfw_mouse_key_proc(GLFWwindow* window, i32 button, i32 action, i32 mods)
{

}
static void glfw_keyboard_key_proc(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods)
{

}
static void glfw_mouse_pos_proc(GLFWwindow* window, r64 x, r64 y)
{
  mouse_position[0] = (r32)x;
  mouse_position[1] = (r32)y;
}

static void gl_debug_proc(u32 source, u32 type, u32 id, u32 severity, i32 length, i8 const* msg, void const* user_param)
{
  switch (severity)
  {
    case GL_DEBUG_SEVERITY_NOTIFICATION: break;
    case GL_DEBUG_SEVERITY_LOW: printf("Severity:Low Type:0x%x Message:%s\n", type, msg); break;
    case GL_DEBUG_SEVERITY_MEDIUM: printf("Severity:Medium Type:0x%x Message:%s\n", type, msg); break;
    case GL_DEBUG_SEVERITY_HIGH: printf("Severity:High Type:0x%x Message:%s\n", type, msg); break;
  }
}

void engine_update()
{
  update_step();
}
void engine_render()
{
  if ((time - prev_render_time) >= ticks_render)
  {
    renderer_new_frame();
    glfwSwapBuffers(window);
    prev_render_time = time;
  }
}
void engine_physic()
{
  if ((time - prev_physic_time) >= ticks_physic)
  {
    physic_step(0.1f);
    prev_physic_time = time;
  }
}
void engine_sound()
{
  sound_step();
}

i32 main()
{
  glfwSetErrorCallback(glfw_debug_proc);
  if (glfwInit())
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_SAMPLES, 16);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    window = glfwCreateWindow((i32)window_size[0], (i32)window_size[1], "", NULL, NULL);
    if (window)
    {
      glfwSetWindowCloseCallback(window, glfw_close_proc);
      glfwSetWindowSizeCallback(window, glfw_resize_proc);
      glfwSetMouseButtonCallback(window, glfw_mouse_key_proc);
      glfwSetKeyCallback(window, glfw_keyboard_key_proc);
      glfwSetCursorPosCallback(window, glfw_mouse_pos_proc);
      glfwMakeContextCurrent(window);
      glfwSwapInterval(0);
      if (gladLoadGL())
      {
        glDebugMessageCallback(gl_debug_proc, 0);
        glEnable(GL_DEBUG_OUTPUT);
        status |= asset_db_create();
        status |= ecs_create();
        status |= update_create();
        status |= renderer_create();
        status |= physic_create();
        status |= sound_create();
        status |= sandbox_create();
        while (status == 0)
        {
          time = (r32)glfwGetTime();
          delta_time = time - prev_time;
          events_poll(window);
          engine_update();
          engine_render();
          engine_physic();
          engine_sound();
          prev_time = time;
        }
        sandbox_destroy();
        sound_destroy();
        physic_destroy();
        renderer_destroy();
        update_destroy();
        ecs_destroy();
        asset_db_destroy();
      }
      else
      {
        printf("Failed loading GL\n");
      }
      glfwDestroyWindow(window);
    }
    else
    {
      printf("Failed creating window\n");
    }
    glfwTerminate();
  }
  else
  {
    printf("Failed initializing GLFW\n");
  }
  return 0;
}