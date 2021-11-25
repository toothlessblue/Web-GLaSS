#version 300 es
precision mediump float;

out vec4 color;
in vec2 fUv;

uniform sampler2D fontAtlas;
uniform vec3 textColour;

void main()
{    
    float textureValue = texture(fontAtlas, fUv).r;
    color = vec4(textColour, textureValue);
}  