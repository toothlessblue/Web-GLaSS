# Fragment shaders
```glsl
#version 300 es				// MUST start with this exact version tag
precision mediump float;	// MUST define float precision - level is arbitrary

void main() { 				// MUST have a main function
   color = vec4(1,1,1,1);   // MUST set color with vec4 (I think)
}
```

# Vertex shaders
```glsl
#version 300 es				// MUST start with this exact version tag
precision mediump float;	// MAY define float precision - level is arbitrary

void main() {				// MUST have a main function
	...
}
```

# Float precision
`mediump` float precision is prefered, it's a good balance between quality and performance, but both `lowp` and `highp` can also be used.

It is prefered to have precision defined in vertex shaders even if not required, for clarity. But you can save the 26 bytes if you want. `mediump` is the default.