#version 300 es
precision mediump float;

layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4 MVP_matrix;

out vec4 fragmentColor;

void main() {
	gl_Position = MVP_matrix * vec4(vertexPosition_modelspace, 1);
	fragmentColor = vec4(vertexPosition_modelspace, 1);
}