#version 300 es
precision mediump float;

layout(location = 0) in vec3 vVertex;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

uniform float radius;

void main(){
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix * vec4(vVertex * radius * 2.0f, 1));
}