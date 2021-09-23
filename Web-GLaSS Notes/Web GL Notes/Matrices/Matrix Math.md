More detailed explanation: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/

# Translation
```cpp
include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
glm::mat4 myMatrix = glm::translate(glm::mat4(), glm::vec3(10.0f, 0.0f, 0.0f)); glm::vec4 myVector(10.0f, 10.0f, 10.0f, 0.0f);
glm::vec4 transformedVector = myMatrix * myVector;
```

# Scaling
```cpp
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
glm::mat4 myScalingMatrix = glm::scale(2.0f, 2.0f ,2.0f);
```

# Rotation
```cpp
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
glm::vec3 myRotationAxis( ??, ??, ??);
glm::rotate( angle_in_degrees, myRotationAxis );
```

# Cumulating Transforms
```cpp
TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;
```
It's important multiplication is done in this order
1. Translation
2. Rotation
3. Scaling
4. Original

In reality, it happens in reverse to intuition - scaling happens first, then rotation, then translation. This is important because:
- You have a boat, if you move it 10 units on the x axis and then scale it by 2, you now have a large boat on 20x, when you really want it on 10x
- Instead, if you scale it by 2, and then move it 10 units, you now have a large boat on 10x

# Calculating an objects camera coordinates
1. Multiply model coordinates by the [[Model Matrix]] to get the world coordinates
2. Multiply world coordinates by [[Camera or View Matrix]] to get camera coordinates
3. Multiply camera coordinates by the [[Projection Matrix]] to get "homogenous coordinates", this name sucks, I'm going to call them "screen coordinates"

This looks like
```cpp
glm::mat4 MVPmatrix = projection * view * model;
```
And to apply it in GLSL
```glsl
transformed_vertex = MVPmatrix * in_vertex;
```