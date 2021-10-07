#version 300 es
precision mediump float;
out vec4 color;
  
in vec2 texCoords;

uniform sampler2D screenTexture;

void main()
{
    color = texture(screenTexture, texCoords);
}