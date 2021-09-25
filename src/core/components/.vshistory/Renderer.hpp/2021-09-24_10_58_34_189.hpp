class Renderer {
public:
	Renderer() {

	}

	GLfloat getVertices() {
		GLfloat g_vertex_buffer_data[] = {
		   -1.0f, -1.0f, 0.0f,
		   1.0f, -1.0f, 0.0f,
		   0.0f,  1.0f, 0.0f,
		};

		return g_vertex_buffer_data;
	}
};