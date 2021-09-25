#version 100
precision mediump float;

void main() {
    gl_FragColor = vec4(gl_FragCoord.x / 800.0, gl_FragCoord.y / 500.0, 1, 1);
}