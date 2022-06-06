#version 460 core

layout(location = 0) in vec4 position;
layout(location = 0) in vec4 normal;
layout(location = 1) in vec4 color;
layout(location = 1) in vec2 uv;

layout(location = 0) out vertex_t
{
  vec4 color;
  vec4 normal;
  vec2 uv;
} vertex;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
  vertex.normal = normal;
  vertex.color = color;
  vertex.uv = uv;
  gl_Position = projection * view * model * position;
}