This [[Component]] stores positional information about a [[GameObject]]. Every [[GameObject]] has one automatically added to its [[Component]] list and has a special `->transform` property for it.

Inherits [[Component]]

Contains 3 vectors
- Position
- Rotation
- Scale

Provides functions to get matrices for all vectors, this is mostly for rendering
`glm::mat4 getTranslationMatrix`
`glm::mat4 getScaleMatrix`
`glm::mat4 getRotationMatrix`

And a function to get the combined [[Model Matrix]]
`glm::mat4 getModelMatrix`

Also provides `glm::mat4 getModelViewProjectionMatrix`, but this is maybe poor placement, as it requires [[View matrix]] and [[Projection Matrix]] which both come from the [[Camera]]. 

A Transform may be replaced by a [[RectTransform]], which inherits Transform and provides a number of extra functions for use with UIs.