#include "../RenderPipeline/RenderPipeline.hpp"
#include "../Screen/Screen.hpp"

class Engine {
public:
    Engine();
    RenderPipeline* pipeline;
    Screen* screen;
};
