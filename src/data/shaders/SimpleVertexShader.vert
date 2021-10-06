#version 300 es
precision mediump float;

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vVertex;
layout(location = 1) in vec2 vUv;
layout(location = 2) in vec3 vNormal;

// Output data ; will be interpolated for each fragment.
out vec2 fUv;
out vec3 fNormal;

// Values that stay constant for the whole mesh.
uniform mat4 MVP_matrix;

void main(){
	gl_Position = MVP_matrix * vec4(vVertex, 1);

    fUv = vUv;
    fNormal = vNormal;
}