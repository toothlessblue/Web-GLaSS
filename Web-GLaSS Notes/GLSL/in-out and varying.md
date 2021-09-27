GLSL 3.3 has the keywords `in` and `out` that allow passing information between vertex and fragment shaders. These cannot be used because WebGL uses 1.0

However, GLSL ES 1.0 has the equivalent `varying` keyword

SimpleFragmentShader.frag
```glsl
#version 100
precision mediump float;

varying vec4 fragmentColor;

void main() {
   gl_FragColor = fragmentColor;
}
```
SimpleVertexShader.vert
```glsl
#version 100
precision mediump float;

attribute vec3 vertexPosition_modelspace;

varying vec4 fragmentColor;

void main() {
   gl_Position = vec4(vertexPosition_modelspace, 1);
   fragmentColor = vec4(vertexPosition_modelspace, 1);
}
```
Here, the vert shader passes the vec4 variable "fragmentColor" to the frag shader, the frag shader has an exact equal variable name "fragmentColor". Both have the varying keyword.