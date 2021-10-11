#version 100
precision mediump float;

void main() {
    gl_FragColor = vec4(gl_FragCoord.x / 800, gl_FragCoord.y / 500, gl_FragCoord.x / gl_FragCoord.y, 1);
}