#include "Mesh.hpp"

Mesh::Mesh() {
    GLuint ids[4];
    glGenBuffers(4, &ids[0]);

    this->vertexBuffer = ids[0];
    this->uvBuffer = ids[1];
    this->normalsBuffer = ids[2];
    this->trianglesBuffer = ids[3];
}

// TODO learning this may be a pain
void Mesh::recalculateNormals() {

}

void Mesh::setVertices(GLfloat* vertices, int size) {
    this->vertices = vertices;
    this->triangleCount = size / sizeof(GLfloat);

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, this->vertices, GL_STATIC_DRAW);
}

void Mesh::setUVs(GLfloat* uvs, int size) {
    this->uvs = uvs;

    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, this->uvs, GL_STATIC_DRAW);
}

void Mesh::setNormals(GLfloat* normals, int size) {
    this->normals = normals;

    glBindBuffer(GL_ARRAY_BUFFER, this->normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, this->normals, GL_STATIC_DRAW);
}

void Mesh::setTriangles(unsigned int* triangles, int size) {
    this->triangles = triangles;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->trianglesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, this->triangles, GL_STATIC_DRAW);
}


GLfloat* Mesh::getVertices() {
    return this->vertices;
}

GLfloat* Mesh::getUVs() {
    return this->uvs;
}

GLfloat* Mesh::getNormals() {
    return this->normals;
}

unsigned int* Mesh::getTriangles() {
    return this->triangles;
}


void Mesh::draw() {
    // Bind the UVs of the triangles to render
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
    glVertexAttribPointer(
        1,                    // attribute 1
        2,                    // size - vec2
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        0,                    // stride
        (void*)0              // array buffer offset
    );

    // Bind the normals of the triangles to render
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, this->normalsBuffer);
    glVertexAttribPointer(
        2,                    // attribute 2
        3,                    // size - vec3
        GL_FLOAT,             // type
        GL_FALSE,              // normalized?
        0,                    // stride
        (void*)0              // array buffer offset
    );

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glVertexAttribPointer(
        0,                    // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                    // size - vec3
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        0,                    // stride
        (void*)0              // array buffer offset
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->trianglesBuffer);

    // Draw the triangles !
    glDrawElements(
        GL_TRIANGLES,             // mode
        this->triangleCount,      // count
        GL_UNSIGNED_INT,          // type
        (void*)0                  // element array buffer offset
    );
}