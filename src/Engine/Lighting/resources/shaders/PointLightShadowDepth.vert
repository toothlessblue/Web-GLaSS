#version 300 es
precision mediump float;

layout(location = 0) in vec3 vVertex;
uniform mat4 modelMatrix;
uniform mat4 shadowMatrix;

out vec3 fragPos;

void main()
{
    gl_Position = shadowMatrix * modelMatrix * vec4(vVertex, 1.0);
    fragPos = vec3(modelMatrix * vec4(vVertex, 1));
}  