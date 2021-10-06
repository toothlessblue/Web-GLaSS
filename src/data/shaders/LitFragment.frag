#version 300 es
#define MAX_LIGHTS 128
precision mediump float;

struct Light {
    int type; // from -1: Light, PointLight, DirectionalLight, OmnidirectionalLight
    vec3 position;
    vec3 colour;
    float intensity;
    float maxDistance;
};

in vec2 fUv;
in vec3 fNormal;

out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

uniform Light lights[MAX_LIGHTS];
uniform int lightCount;

void main() {
    // Output color = color of the texture at the specified UV
    color = texture(myTextureSampler, fUv).rgb;

    for (int i = 0; i < lightCount; i++) {
        Light light = lights[i];

        if (light.type == 0) { // point light
            

        } else if (light.type == 1) { // directional light
            

        } else if (light.type == 2) { // omnidirectional light


        }
    }
}