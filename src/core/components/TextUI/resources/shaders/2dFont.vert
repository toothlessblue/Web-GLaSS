#version 300 es
precision mediump float;

layout (location = 0) in vec3 vVertex;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vUv;

out vec2 fUv;

uniform mat4 modelMatrix;

void main()
{
	gl_Position = modelMatrix * vec4(vVertex.xy, 0.0, 1.0);
    fUv = vUv;
}  