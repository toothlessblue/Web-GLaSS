#include "./MeshRenderer.hpp"

class TriangleRenderer : MeshRenderer {
public:
	TriangleRenderer() {
		glGenVertexArrays(1, &this->vertexArrayID);

		// Generate 1 buffer, put the resulting identifier in vertexbuffer
		glGenBuffers(1, &this->vertexbuffer);
		// The following commands will talk about our 'vertexbuffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	}

	void render() override {
		glBindVertexArray(this->vertexArrayID);

		// glUseProgram(this->programID; // TODO allow renderers to have seperate programs for unique shaders each

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0); // Don't fully understand this
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
		glVertexAttribPointer(
			0,                    // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                    // size
			GL_FLOAT,             // type
			GL_FALSE,             // normalized?
			0,                    // stride
			(void*)0              // array buffer offset
		);
		// Draw the triangle!
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);
	}
private:
	static const GLfloat g_vertex_buffer_data[] = {
		   -1.0f, -1.0f, 0.0f,
		   1.0f, -1.0f, 0.0f,
		   0.0f,  1.0f, 0.0f,
	};

	GLuint vertexArrayID;
	GLuint vertexbuffer;
};