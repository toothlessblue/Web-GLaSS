#version 300 es
precision mediump float;

in vec2 fUv;
in vec3 fNormal;
in vec3 fragPos;

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedo;

uniform sampler2D fontAtlas;
uniform vec3 textColour;

void main()
{    
    float textureValue = texture(fontAtlas, fUv).r;

    gAlbedo = vec4(textColour * textureValue, textureValue); // TODO seperate render pass for unlit objects
    gNormal = fNormal;
    gPosition = fragPos;
}  