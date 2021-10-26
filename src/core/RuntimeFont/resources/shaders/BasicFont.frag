#version 300 es
precision mediump float;

in vec2 TexCoords;
out vec4 colour;

uniform sampler2D text;
uniform vec3 textColour;

void main()
{    
    colour = vec4(textColour, texture(text, TexCoords).r);
}  