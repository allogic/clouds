#version 460 core

layout(location = 0) in vertex_t
{
  vec2 uv;
} vertex;

layout(location = 0) out vec4 color;

uniform sampler2D text;
uniform vec3 text_color;

void main()
{
  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, vertex.uv).r);
  color = vec4(text_color, 1.0) * sampled;
}