#include "./MeshRenderer.hpp"

class TriangleRenderer : MeshRenderer {
public:
	TriangleRenderer() {
		glGenVertexArrays(1, &this->vertexArrayID);

		static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
		};
	}

	void render() override {
		glBindVertexArray(this->vertexArrayID);
	}
private:
	GLuint vertexArrayID;
};