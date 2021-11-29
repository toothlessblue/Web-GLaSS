Inherits [[Component]]

```cpp
float fieldOfView;
float ratio;
float nearClipPlane;
float farClipPlane;
```
 
 The clip planes define the range to render objects within. Anything closer to the camera than the nearClipPlane, or further than the farClipPlane, are not rendered at all.
 
 