#version 300 es
precision mediump float;

layout (location = 0) in vec3 vVertex;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vUv;

out vec2 fUv;
out vec3 fragPos;
out vec3 fNormal;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vVertex, 1);
    fUv = vUv;
    fragPos = vec3(modelMatrix * vec4(vVertex, 1));
    fNormal = vNormal;
}  