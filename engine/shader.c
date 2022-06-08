#include <stdio.h>
#include <string.h>

#include <core/file_system.h>

#include <glad/glad.h>

#include <shader.h>

u8 shader_check_compile_status(u32 shader_id)
{
  i32 compile_status = 0;
  i32 info_log_length = 0;
  i8* info_log = NULL;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);
  if (compile_status == 0)
  {
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0)
    {
      info_log = (i8*)malloc(info_log_length);
      if (info_log != NULL)
      {
        glGetShaderInfoLog(shader_id, info_log_length, &info_log_length, info_log);
        printf(info_log);
        free(info_log);
      }
    }
    return 1;
  }
  return 0;
}
u8 shader_check_link_status(u32 program_id)
{
  i32 link_status = 0;
  i32 info_log_length = 0;
  i8* info_log = NULL;
  glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
  if (link_status == 0)
  {
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    if (info_log_length > 0)
    {
      info_log = (i8*)malloc(info_log_length);
      if (info_log != NULL)
      {
        glGetProgramInfoLog(program_id, info_log_length, &info_log_length, info_log);
        printf(info_log);
        free(info_log);
      }
    }
    return 1;
  }
  return 0;
}

u8 shader_create(shader_t* shader)
{
  u8 status = 1;
  shader->pid = glCreateProgram();
  if (shader->pid != 0)
  {
    switch (shader->type)
    {
      case shader_render:
      {
        u32 vertex_id = glCreateShader(GL_VERTEX_SHADER);
        if (vertex_id != 0)
        {
          u8* vertex_source = file_load(shader->files[0]);
          if (vertex_source != NULL)
          {
            glShaderSource(vertex_id, 1, &vertex_source, NULL);
            glCompileShader(vertex_id);
            if (shader_check_compile_status(vertex_id) == 0)
            {
              glAttachShader(shader->pid, vertex_id);
            }
            free(vertex_source);
          }
        }
        u32 fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
        if (fragment_id != 0)
        {
          u8* fragment_source = file_load(shader->files[1]);
          if (fragment_source != NULL)
          {
            glShaderSource(fragment_id, 1, &fragment_source, NULL);
            glCompileShader(fragment_id);
            if (shader_check_compile_status(fragment_id) == 0)
            {
              glAttachShader(shader->pid, fragment_id);
            }
            free(fragment_source);
          }
        }
        glLinkProgram(shader->pid);
        if (shader_check_link_status(shader->pid) == 0)
        {
          status = 0;
        }
        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id);
        break;
      }
      case shader_compute:
      {
        u32 compute_id = glCreateShader(GL_COMPUTE_SHADER);
        if (compute_id != 0)
        {
          u8* compute_source = file_load(shader->files[2]);
          if (compute_source != NULL)
          {
            glShaderSource(compute_id, 1, &compute_source, NULL);
            glCompileShader(compute_id);
            if (shader_check_compile_status(compute_id) == 0)
            {
              glAttachShader(shader->pid, compute_id);
            }
            free(compute_source);
          }
        }
        glLinkProgram(shader->pid);
        if (shader_check_link_status(shader->pid) == 0)
        {
          status = 0;
        }
        glDeleteShader(compute_id);
        break;
      }
    }
    if (status != 0)
    {
      glDeleteShader(shader->pid);
      shader->pid = 0;
    }
  }
  return status;
}
void shader_bind(shader_t* shader)
{
  glUseProgram(shader->pid);
}
void shader_uniform_r32(shader_t* shader, i8 const* uniform_name, r32 v)
{
  glUniform1f(
    glGetUniformLocation(shader->pid, uniform_name),
    v
  );
}
void shader_uniform_r32m4(shader_t* shader, i8 const* uniform_name, r32m4 m)
{
  glUniformMatrix4fv(
    glGetUniformLocation(shader->pid, uniform_name),
    1,
    0,
    &m[0][0]
  );
}
void shader_execute(shader_t* shader, u32 x, u32 y, u32 z)
{
  glDispatchCompute(x, y, z);
}
void shader_unbind()
{
  glUseProgram(0);
}
void shader_destroy(shader_t* shader)
{
  glDeleteProgram(shader->pid);
  shader->pid = 0;
}