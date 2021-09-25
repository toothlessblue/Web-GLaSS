#include "./Renderer.hpp"

class MeshRenderer : Renderer {
public:
	MeshRenderer() {
		glGenVertexArrays(1, &this->vertexArrayID);
	}
};