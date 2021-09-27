#version 100
precision mediump float;

attribute vec3 vertexPosition_modelspace;
uniform mat4 MVP_matrix;

void main() {
	gl_Position = MVP_matrix * vec4(vertexPosition_modelspace, 1);
}