#pragma once

#include "../../Component/Component.hpp"
#include "../../../../include/glm/glm.hpp"

class Camera : Component {
public:
    float fieldOfView;
    float ratio;
    float nearClipPlane;
    float farClipPlane;

    /**
     * @param fieldOfView The cameras vertical field of view in radians
     * @param ratio Ratio of the screen, to get divide screen width by screen height
     * @param nearClipPlane The closest an object can be before it isn't rendered, objects closer than this distance are clipped.
     * @param farClipPlane The furthest point at which objects are rendered, objects beyond this distance are clipped.
     */
    Camera(float fieldOfView, float ratio, float nearClipPlane, float farClipPlane);

    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();
private:

};
