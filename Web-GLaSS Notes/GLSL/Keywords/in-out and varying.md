GLSL 3.0 has the keywords `in` and `out` that allow passing information between vertex and fragment shaders.

There's the equivalent `varying` keyword from GLSL 1.0, however this is deprecated and actually stops compiling if used.

SimpleFragmentShader.frag
```glsl
#version 300 es
precision mediump float;

in vec4 fragmentColor;
out vec4 color;

void main() {
 color = fragmentColor;
}
```

SimpleVertexShader.vert
```glsl
#version 300 es
precision mediump float;

layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4 MVP_matrix;

out vec4 fragmentColor;

void main() {
   gl_Position = MVP_matrix * vec4(vertexPosition_modelspace, 1);
   fragmentColor = vec4(vertexPosition_modelspace, 1);
}
```
Here, the vert shader passes the vec4 variable "fragmentColor" to the frag shader, the frag shader has an exact equal variable name "fragmentColor". Both have the varying keyword.