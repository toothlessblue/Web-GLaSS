#version 300 es
precision mediump float;

out vec4 color;
in vec2 fUv;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

uniform int pointLightCount;
struct PointLight {
    vec4 position;
    vec4 colour;
    
    float constant;
    float linear;
    float quadratic;
    float brightness;
};

const int NR_LIGHTS_PER_TYPE = 50;

// layout (std140) uniform lights {
//     PointLight pointLights[NR_LIGHTS_PER_TYPE];
// } lightsBlock;

uniform vec3 viewPos;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 albedoSpec)
{
    float distance = length(light.position.xyz - fragPos);

    vec3 lightDir = normalize(light.position.xyz - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), albedoSpec.a);
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * albedoSpec.rgb * light.colour.rgb;
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
    
    return ((diffuse * attenuation) + vec3(spec)) * light.brightness;
} 

void main()
{
    // retrieve data from G-buffer
    vec3 fragPos = texture(gPosition, fUv).rgb;
    vec3 normal = texture(gNormal, fUv).rgb;
    vec4 albedoSpec = texture(gAlbedo, fUv).rgba;
    
    // then calculate lighting as usual
    vec3 lighting = albedoSpec.rgb * 0.1; // hard-coded ambient component
    vec3 viewDir = normalize(viewPos - fragPos);

    // for(int i = 0; i < pointLightCount; ++i)
    // {
    //     lighting += CalcPointLight(lightsBlock.pointLights[i], normal, fragPos, viewDir, albedoSpec);
    // }
    
    color = vec4(lighting.rgb, 1.0);
}