#version 100
precision mediump float;

void main() {
    gl_FragColor = vec4(gl_FragCoord.x, gl_FragCoord.y, gl_FragCoord.z, 1);
}