#version 100
precision mediump float;

attribute vec3 vertexPosition_modelspace;
uniform mat4 MVP_matrix;

varying vec4 fragmentColor;

void main() {
	gl_Position = MVP_matrix * vec4(vertexPosition_modelspace, 1);
	fragmentColor = vec4(vertexPosition_modelspace, 1);
}