#include "Mesh.hpp"

Mesh::Mesh() {
    GLuint ids[4];
    glGenBuffers(4, &ids[0]);

    this->vertexBuffer = ids[0];
    this->uvBuffer = ids[1];
    this->normalsBuffer = ids[2];
    this->indexesBuffer = ids[3];
}

void Mesh::recalculateNormals() {
    std::vector<std::vector<glm::vec3>> vertexToTriangleNormalMap(
        this->indexes.size(),
        std::vector<glm::vec3>()
    );

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

        vertexToTriangleNormalMap[this->indexes[i]] = *(new std::vector<glm::vec3>());

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

    this->setNormals(this->normals);
}

void Mesh::setVertices(std::vector<glm::vec3> vertices) {
    this->vertices = vertices;

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::setUVs(std::vector<glm::vec2> uvs) {
    this->uvs = uvs;

    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::setNormals(std::vector<glm::vec3> normals) {
    this->normals = normals;

    glBindBuffer(GL_ARRAY_BUFFER, this->normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::setIndexes(std::vector<unsigned int> indexes) {
    this->indexes = indexes;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), &this->indexes[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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