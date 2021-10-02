#version 300 es
precision mediump float;

in vec4 fragmentColor;
out vec4 color;

void main() {
    color = fragmentColor;
}