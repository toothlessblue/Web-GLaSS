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

void Mesh::setVertices(std::vector<glm::vec3> vertices) {
    this->vertices = vertices;

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);
}

void Mesh::setUVs(std::vector<glm::vec2> uvs) {
    this->uvs = uvs;

    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);
}

void Mesh::setNormals(std::vector<glm::vec3> normals) {
    this->normals = normals;

    glBindBuffer(GL_ARRAY_BUFFER, this->normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);
}

void Mesh::setTriangles(std::vector<unsigned int> triangles) {
    this->triangles = triangles;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->trianglesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(unsigned int), &this->triangles[0], GL_STATIC_DRAW);
}


std::vector<glm::vec3> Mesh::getVertices() {
    return this->vertices;
}

std::vector<glm::vec2> Mesh::getUVs() {
    return this->uvs;
}

std::vector<glm::vec3> Mesh::getNormals() {
    return this->normals;
}

std::vector<unsigned int> Mesh::getTriangles() {
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
        GL_FALSE,             // normalized?
        0,                    // stride
        (void*)0              // array buffer offset
    );

    // Bind the vertices of the triangles to render
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
        GL_TRIANGLES,               // mode
        this->triangles.size(),     // count
        GL_UNSIGNED_INT,            // type
        (void*)0                    // element array buffer offset
    );
}