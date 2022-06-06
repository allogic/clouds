#version 460 core

layout(location = 0) in vec4 posuv;

layout(location = 0) out vertex_t
{
  vec2 uv;
} vertex;

uniform mat4 projection;

void main()
{
  vertex.uv = posuv.zw;
  gl_Position = projection * vec4(posuv.xy, 0.0, 1.0);
}