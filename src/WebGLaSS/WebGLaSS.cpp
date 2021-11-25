#include "WebGLaSS.hpp"

Screen WebGLaSS::screen = Screen(900, 450);
RenderPipeline WebGLaSS::renderPipeline = RenderPipeline();
WorldSpace WebGLaSS::worldSpace = WorldSpace();

void WebGLaSS::addGameObject(GameObject* newObject) {
    WebGLaSS::worldSpace.addGameObject(newObject);
}