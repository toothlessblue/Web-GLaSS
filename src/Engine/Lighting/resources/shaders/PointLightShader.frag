#version 300 es
precision mediump float;

out vec4 colour;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

uniform samplerCube shadowCubemap;
uniform float shadowFarPlane;

uniform float screenHeight;
uniform float screenWidth;

// TODO use uniform layout
// layout (std140) uniform LightData {
//     vec4 position;
//     vec4 colour;
    
//     float constant;
//     float linear;
//     float quadratic;
// } lightData;

uniform vec3 position;
uniform vec3 lightColour;
uniform float constant;
uniform float linear;
uniform float quadratic;

uniform vec3 viewPos;

float ShadowCalculation(vec3 fragPos)
{
    vec3 fragToLight = fragPos - position; 
    float currentDepth = length(fragToLight);

    float shadow  = 0.0;
    float bias    = 0.05; 
    float samples = 4.0;
    float offset  = 0.1;
    for(float x = -offset; x < offset; x += offset / (samples * 0.5))
    {
        for(float y = -offset; y < offset; y += offset / (samples * 0.5))
        {
            for(float z = -offset; z < offset; z += offset / (samples * 0.5))
            {
                float closestDepth = texture(shadowCubemap, fragToLight + vec3(x, y, z)).r; 
                closestDepth *= shadowFarPlane; // undo mapping [0;1]
                if(currentDepth - bias > closestDepth)
                    shadow += 1.0;
            }
        }
    }
    shadow /= (samples * samples * samples);

    return (1.0 - shadow);
}

vec3 CalcPointLight(vec3 normal, vec3 fragPos, vec3 viewDir, vec4 albedoSpec)
{
    float shadow = ShadowCalculation(fragPos);
    
    float dist = length(position - fragPos);

    vec3 lightDir = normalize(position - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    vec3 spec = pow(max(dot(normal, halfwayDir), 0.0), albedoSpec.a) * lightColour;
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * albedoSpec.rgb * lightColour;
    float attenuation = 1.0 / (constant + linear * dist + quadratic * (dist * dist)); 
    
    return shadow * (diffuse + spec) * attenuation;
} 

void main()
{
    vec2 uv = vec2(gl_FragCoord.x / screenWidth, gl_FragCoord.y / screenHeight);

    // retrieve data from G-buffer
    vec3 fragPos = texture(gPosition, uv).rgb;
    vec3 normal = texture(gNormal, uv).rgb;
    vec4 albedoSpec = texture(gAlbedo, uv).rgba;
    
    // then calculate lighting as usual
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 lighting = CalcPointLight(normal, fragPos, viewDir, albedoSpec);
    
    colour = vec4(lighting, 1.0);
}