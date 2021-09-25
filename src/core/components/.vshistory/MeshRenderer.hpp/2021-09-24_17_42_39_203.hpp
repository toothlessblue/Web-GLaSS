#include "./Renderer.hpp"

class MeshRenderer : Renderer {
public:
	MeshRenderer() {
		glGenVertexArrays(1, &this->vertexArrayID);
	}

	void render() override {
		glBindVertexArray(this->vertexArrayID);
	}
private:
	GLuint vertexArrayID;
};