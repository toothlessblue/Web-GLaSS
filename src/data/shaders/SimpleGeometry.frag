#version 300 es
precision mediump float;

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedo;

in vec2 fUv;
in vec3 fNormal;
in vec3 fragPos;

out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main() {
    // Output color = color of the texture at the specified UV
    color = texture(myTextureSampler, fUv).rgb;

    gPosition = fragPos;
    gNormal = fNormal;

    // and the diffuse per-fragment color
    gAlbedo.rgb = texture(myTextureSampler, fUv).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    gAlbedo.a = texture(myTextureSampler, fUv).r;
}