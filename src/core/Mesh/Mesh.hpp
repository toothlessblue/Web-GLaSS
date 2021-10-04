#pragma once
#include <GL/glew.h>
#include "../../../include/glm/glm.hpp"

class Mesh {
public:
    Mesh();

    void recalculateNormals();

    void setVertices(GLfloat* vertices, int size);
    void setUVs(GLfloat* uvs, int size);
    void setNormals(GLfloat* normals, int size);
    void setTriangles(unsigned int* vertices, int size);

    GLfloat* getVertices();
    GLfloat* getUVs();
    GLfloat* getNormals();
    unsigned int* getTriangles();

    void draw();
private:
    GLuint vertexBuffer;
    GLuint uvBuffer;
    GLuint trianglesBuffer;
    GLuint normalsBuffer;

    GLfloat* vertices;
    unsigned int* triangles;
    unsigned int triangleCount;

    GLfloat* uvs;
    GLfloat* normals;
};