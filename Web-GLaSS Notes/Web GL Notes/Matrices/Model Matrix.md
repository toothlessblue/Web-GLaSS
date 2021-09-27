Each [[GameObject]] in the scene has this matrix, and it defines the objects position, rotation, and scale.

It's made up by multiplying these 3 matrices:
- [[Translation Matrix]]
- [[Rotation Matrix]]
- [[Scale Matrix]]

`modelMatrix = translationMatrix * rotationMatrix * scaleMatrix`

Refer to [[Matrix Math]] for more details