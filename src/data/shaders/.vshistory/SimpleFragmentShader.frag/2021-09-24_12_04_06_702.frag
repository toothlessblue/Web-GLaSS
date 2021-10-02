#version 100
precision mediump float;

void main() {
    gl_FragColor = vec4(gl_Position.x, gl_Position.y, gl_Position.z, 1);
}