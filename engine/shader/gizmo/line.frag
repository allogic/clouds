#version 460 core

layout(location = 0) in vertex_t
{
  vec4 color;
} vertex;

layout(location = 0) out vec4 color;

void main()
{
  color = vertex.color;
}