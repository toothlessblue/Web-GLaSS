#version 300 es
precision mediump float;

in vec3 fragPos;

uniform vec3 lightPosition;
uniform float farPlane;

void main()
{
    // get distance between fragment and light source
    float lightDistance = length(fragPos.xyz - lightPosition);
    
    // map to [0;1] range by dividing by farPlane
    lightDistance = lightDistance / farPlane;
    
    // write this as modified depth
    gl_FragDepth = lightDistance;
}  
