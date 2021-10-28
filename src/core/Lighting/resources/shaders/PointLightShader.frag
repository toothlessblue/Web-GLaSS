#version 300 es
precision mediump float;

out vec4 color;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

// TODO use uniform layout
// layout (std140) uniform LightData {
//     vec4 position;
//     vec4 colour;
    
//     float constant;
//     float linear;
//     float quadratic;
// } lightData;

uniform vec3 position;
uniform vec3 colour;
uniform float constant;
uniform float linear;
uniform float quadratic;

uniform vec3 viewPos;

vec3 CalcPointLight(vec3 normal, vec3 fragPos, vec3 viewDir, vec4 albedoSpec)
{
    float dist = length(position - fragPos);

    vec3 lightDir = normalize(position - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    vec3 spec = pow(max(dot(normal, halfwayDir), 0.0), albedoSpec.a) * colour;
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * albedoSpec.rgb * colour;
    float attenuation = 1.0 / (constant + linear * dist + quadratic * (dist * dist)); 
    
    return (diffuse + spec) * attenuation;
} 

void main()
{
    vec2 uv = vec2(gl_FragCoord.x / 900.0f, gl_FragCoord.y / 450.0f); // TODO get screen resolution from uniform

    // retrieve data from G-buffer
    vec3 fragPos = texture(gPosition, uv).rgb;
    vec3 normal = texture(gNormal, uv).rgb;
    vec4 albedoSpec = texture(gAlbedo, uv).rgba;
    
    // then calculate lighting as usual
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 lighting = CalcPointLight(normal, fragPos, viewDir, albedoSpec);
    
    color = vec4(lighting, 1.0);
}