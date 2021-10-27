#version 300 es
precision mediump float;

in vec2 fUv;

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedo;

uniform sampler2D text;
uniform vec3 textColour;

void main()
{    
    gAlbedo = vec4(textColour, texture(text, fUv).r);
    gNormal = vec3(0, 0, 0);
    gPosition = vec3(0, 0, 0);

    gAlbedo = vec4(1,1,1,1);
}  