#version 300 es
precision mediump float;

layout (location = 0) in vec3 vVertex;
layout (location = 1) in vec2 vUv;

out vec2 fUv;

void main()
{
    gl_Position = vec4(vVertex.x, vVertex.y, vVertex.z, 1.0); 
    fUv = vUv;
}  