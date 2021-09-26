#version 100
precision mediump float;

void main() {
    gl_FragColor = vec4(gl_FragCoord.x / 900.0, gl_FragCoord.y / 450.0, 1, 1);
}