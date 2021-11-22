#version 300 es
precision mediump float;

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUv;

// Output data ; will be interpolated for each fragment.
out vec2 fUv;
out vec3 fNormal;
out vec3 fragPos;

// Values that stay constant for the whole mesh.
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 rotationMatrix;

void main(){
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vVertex, 1);

    fUv = vUv;
    fNormal = vec3(rotationMatrix * vec4(vNormal, 1));
    fragPos = vec3(modelMatrix * vec4(vVertex, 1));
}