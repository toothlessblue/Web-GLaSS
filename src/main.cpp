#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <emscripten.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/quaternion.hpp"
#include "../include/glm/gtx/quaternion.hpp"

// Game engine stuffs
#include "WebGLaSS/WebGLaSS.hpp"
#include "WebGLaSS/RuntimeFont/RuntimeFont.hpp"
#include "WebGLaSS/Input/Input.hpp"
#include "WebGLaSS/Time/Time.hpp"
#include "WebGLaSS/Texture/Texture.hpp"

extern "C" void Start();
extern "C" void Update();

extern "C" void gameLoop() {
    Time::frameStart();
    
    Input::Mouse::doLoop();
    WebGLaSS::renderPipeline.render();
    WebGLaSS::worldSpace.updateGameObjects();

    Update();

    Time::frameEnd();
    Time::incrementFrameCounter();
}

extern "C" int main(int argc, char** argv) {
    emscripten_set_main_loop(gameLoop, 0, 0);
    RuntimeFont::init();
    GenericTextures::generate();

    Start();

    WebGLaSS::worldSpace.startGameObjects();
    return 0;
}