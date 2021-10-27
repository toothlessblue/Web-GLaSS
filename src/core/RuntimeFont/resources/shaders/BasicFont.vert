#version 300 es
precision mediump float;

layout (location = 0) in vec3 vVertex;
layout (location = 2) in vec2 vUv;

out vec2 fUv;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vVertex, 1);
    fUv = vUv;
}  