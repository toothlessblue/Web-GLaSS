#version 300 es
precision mediump float;

out vec4 color;
in vec2 fUv;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    float power;
    float radius;

    vec3 color;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    
    float angle;
    float constant;
    float linear;
    float quadratic;
    float power;

    vec3 color;
};

struct DirectionalLight {
    vec3 direction;
    float power; 
    vec3 color;
};

const int NR_LIGHTS_PER_TYPE = 50;

layout (std140) uniform lights {
    PointLight pointLights[NR_LIGHTS_PER_TYPE];
    SpotLight spotLights[NR_LIGHTS_PER_TYPE];
    DirectionalLight directionalLights[NR_LIGHTS_PER_TYPE];
};

uniform vec3 viewPos;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 albedoSpec)
{
    float distance = length(light.position - fragPos);
    if (distance > light.radius) return vec3(0);

    vec3 lightDir = normalize(light.position - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), albedoSpec.a);
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * albedoSpec.rgb * light.color;
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
    
    return ((diffuse * attenuation) + vec3(spec)) * light.power;
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 albedoSpec)
{
    return vec3(0); // TODO find or make an implementation

    // Is frag pos behind spotlight? return 0
    // 
} 

vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec4 albedoSpec)
{
    vec3 lightDir = normalize(-light.direction);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), albedoSpec.a);
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * albedoSpec.rgb * light.color;
    return (diffuse + vec3(spec)) * light.power;
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

    for(int i = 0; i < NR_LIGHTS_PER_TYPE; ++i)
    {
        lighting += CalcPointLight(pointLights[i], normal, fragPos, viewDir, albedoSpec);
        lighting += CalcDirectionalLight(directionalLights[i], normal, fragPos, viewDir, albedoSpec);
        lighting += CalcSpotLight(spotLights[i], normal, fragPos, viewDir, albedoSpec);
    }
    
    color = vec4(lighting, 1.0);
}