#include "Mesh.hpp"

Mesh::Mesh() {
    GLuint ids[4];
    glGenBuffers(4, &ids[0]);

    this->vertexBuffer = ids[0];
    this->uvBuffer = ids[1];
    this->normalsBuffer = ids[2];
    this->indexesBuffer = ids[3];

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glVertexAttribPointer(
        0,                    // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                    // size - vec3
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        0,                    // stride
        (void*)0              // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
    glVertexAttribPointer(
        1,                    // attribute 1
        2,                    // size - vec2
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        0,                    // stride
        (void*)0              // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, this->normalsBuffer);
    glVertexAttribPointer(
        2,                    // attribute 2
        3,                    // size - vec3
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        0,                    // stride
        (void*)0              // array buffer offset
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void Mesh::recalculateNormals() {
    std::vector<std::vector<glm::vec3>> vertexToTriangleNormalMap;

    // Loop through every triangle
    for (int i = 0; i < this->indexes.size(); i += 3) {
        // Get each vertex for the triangle
        glm::vec3 a = this->vertices[this->indexes[i    ]];
        glm::vec3 b = this->vertices[this->indexes[i + 1]];
        glm::vec3 c = this->vertices[this->indexes[i + 2]];

        // Calculate the surface normal
        glm::vec3 edge1 = b - a;
        glm::vec3 edge2 = c - a;

        glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));
        vertexToTriangleNormalMap[this->indexes[i    ]].push_back(normal);
        vertexToTriangleNormalMap[this->indexes[i + 1]].push_back(normal);
        vertexToTriangleNormalMap[this->indexes[i + 2]].push_back(normal);
    }

    this->normals.clear();

    for (int i = 0; i < this->vertices.size(); i++) {
        glm::vec3 totalNormal;

        for (glm::vec3 normal : vertexToTriangleNormalMap[i]) {
            totalNormal += normal;
        }

        glm::vec3 vertexNormal = glm::normalize(totalNormal);

        this->normals.push_back(vertexNormal);
    }
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

void Mesh::setIndexes(std::vector<unsigned int> indexes) {
    this->indexes = indexes;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), &this->indexes[0], GL_STATIC_DRAW);
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

std::vector<unsigned int> Mesh::getIndexes() {
    return this->indexes;
}


void Mesh::draw() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexesBuffer);

    // Draw the triangles !
    glDrawElements(
        GL_TRIANGLES,               // mode
        this->indexes.size(),       // count
        GL_UNSIGNED_INT,            // type
        (void*)0                    // element array buffer offset
    );
}