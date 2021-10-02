#version 300 es
precision mediump float;

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 MVP_matrix;

void main(){
	gl_Position = MVP_matrix * vec4(vertexPosition_modelspace, 1);

    // UV of the vertex. No special space for this one.
    UV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}