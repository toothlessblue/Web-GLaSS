#include "./MeshRenderer.hpp"

class TriangleRenderer : MeshRenderer {
public:
	TriangleRenderer() {
		glGenVertexArrays(1, &this->vertexArrayID);
	}

	void render() override {

	}
};