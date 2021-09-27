[[Matrix Math]]

Defines where the [[Camera]] is and the direction it's pointing in.

Every vertex in the scene should be multiplied by this matrix to simulate the camera position and rotation

```cpp
glm::mat4 CameraMatrix = glm::lookAt( 
	cameraPosition, // the position of your camera, in world space 
	cameraTarget, // where you want to look at, in world space 
	upVector // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
);
```

To use a direction vector instead of a target, add it to cameraPosition and use that as the target. Further explaination bellow

From https://stackoverflow.com/questions/21830340/understanding-glmlookat
> The `up` vector is basically a vector defining your world's "upwards" direction. In almost all normal cases, this will be the vector `(0, 1, 0)` i.e. towards positive Y. `eye` is the position of the camera's viewpoint, and `center` is where you are looking at (a position). If you want to use a direction vector `D` instead of a center position, you can simply use `eye + D` as the center position, where `D` can be a unit vector for example.
> 
>  As for the inner workings, or more details, this is a common basic function for building a view matrix. Try reading the docs for [gluLookAt()](http://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml) which is functionally equivalent."