#version 300 es
precision mediump float;

out vec4 color;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

uniform float screenHeight;
uniform float screenWidth;

uniform float power;

void main()
{
    vec2 uv = vec2(gl_FragCoord.x / screenWidth, gl_FragCoord.y / screenHeight);
    vec4 albedoSpec = texture(gAlbedo, uv).rgba;
    
    color = vec4(albedoSpec.rgb, 1.0) * power;
}