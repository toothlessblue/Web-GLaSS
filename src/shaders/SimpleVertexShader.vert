#version 100
precision mediump float;

attribute vec4 vertexPosition_modelspace;

void main() {
	gl_Position.xyz = vertexPosition_modelspace.xyz / vec3(3,3,3);
	gl_Position.w = 1.0;
}