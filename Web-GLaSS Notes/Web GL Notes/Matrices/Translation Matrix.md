```cpp
include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
glm::mat4 myMatrix = glm::translate(glm::mat4(), positionVector); glm::vec4 myVector(10.0f, 10.0f, 10.0f, 0.0f);
glm::vec4 transformedVector = myMatrix * myVector;
```

Where `positionVector` is a `glm::vec3` that defines the objects position