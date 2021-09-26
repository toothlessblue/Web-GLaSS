#version 100
precision mediump float;

attribute vec4 vertexPosition_modelspace;
uniform mat4 MVP_matrix;

void main() {
	gl_Position = vertexPosition_modelspace * MVP_matrix;
}