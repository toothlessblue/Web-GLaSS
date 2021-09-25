#include <GL/glew.h>

class Renderer {
public:
	Renderer() {
		glGenVertexArrays(1, &this->vertexArrayID);
	}

	virtual void render() {
		glBindVertexArray(vertexArrayID);
	}
private:
	GLuint vertexArrayID;
};