#version 300 es
precision mediump float;

out vec4 color;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

uniform float power;

void main()
{
    vec2 uv = vec2(gl_FragCoord.x / 900.0f, gl_FragCoord.y / 450.0f); // TODO get screen resolution from uniform
    vec4 albedoSpec = texture(gAlbedo, uv).rgba;
    
    color = vec4(albedoSpec.rgb, 1.0) * power * 9.0; // TODO remove 9 multiple
}