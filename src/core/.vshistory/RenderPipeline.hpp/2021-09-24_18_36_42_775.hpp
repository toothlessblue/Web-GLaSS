#include <GL/glew.h>
#include <list>

#include "./components/TriangleRenderer.hpp"

class RenderPipeline {
public:
    GLuint programID;
    GLuint vertexbuffer;

    std::list<Renderer> renderers;

	RenderPipeline() {
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);

        static const GLfloat g_vertex_buffer_data[] = {
           -1.0f, -1.0f, 0.0f,
           1.0f, -1.0f, 0.0f,
           0.0f,  1.0f, 0.0f,
        };

        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &this->vertexbuffer);
        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        this->renderers.push_back(TriangleRenderer());
	}

    void setProgram(GLuint programID) {
        this->programID = programID;
    }

	void render() {
        std::cout << "RenderPipeline render \n";

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(this->programID); // TODO place this in render function of each renderer to allow seperate shaders for different renderers

        for (Renderer const& renderer : this->renderers) {
            renderer->render();
        }
	}
};