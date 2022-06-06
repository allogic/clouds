#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

layout(location = 0) out vertex_t
{
  vec4 color;
} vertex;

uniform mat4 projection;
uniform mat4 view;

void main()
{
  vertex.color = color;
  gl_Position = projection * view * position;
}