#pragma once
#include "../../../../include/glm/glm.hpp"
#include "../../../../include/glm/gtx/transform.hpp"
#include "../../../../include/glm/gtc/matrix_transform.hpp"
#include "../../GameEngine/GameEngine.hpp"
#include "../../Component/Component.hpp"

class Camera : public Component {
public:
    float fieldOfView;                      // fieldOfView The cameras vertical field of view in radians
    float ratio;                            // ratio Ratio of the screen, to get divide screen width by screen height
    float nearClipPlane;                    // nearClipPlane The closest an object can be before it isn't rendered, objects closer than this distance are clipped.
    float farClipPlane;                     // farClipPlane The furthest point at which objects are rendered, objects beyond this distance are clipped.

    Camera();

    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();

    void setAsActiveCamera();
private:

};
