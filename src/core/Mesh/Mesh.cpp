#include "Mesh.hpp"
#include <iostream>

Mesh::Mesh() {
    GLuint ids[2];
    glGenBuffers(2, &ids[0]);

    this->vertexBuffer = ids[0];
    this->indexBuffer = ids[1];
}

void Mesh::recalculateNormals() {
    std::vector<glm::vec3> newNormals;

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

    for (int i = 0; i < this->vertices.size(); i++) { // for every vertex
        glm::vec3 totalNormal = glm::vec3(0,0,0);

        for (glm::vec3 normal : vertexToTriangleNormalMap[i]) { // add up connected normals
            totalNormal += normal;
        }

        glm::vec3 vertexNormal = glm::normalize(totalNormal); // normalise result

        newNormals.push_back(vertexNormal);
    }
    
    this->setNormals(newNormals);
}

void Mesh::setVertices(std::vector<glm::vec3> vertices) {
    this->vertices = vertices;
}

void Mesh::setUVs(std::vector<glm::vec2> uvs) {
    this->uvs = uvs;
}

void Mesh::setNormals(std::vector<glm::vec3> normals) {
    this->normals = normals;
}

void Mesh::setIndexes(std::vector<unsigned int> indexes) {
    if (indexes.size() % 3 != 0) {
        std::cerr << "Size of indexes is not a multiple of 3, this may be malformed." << std::endl;
    }

    this->indexes = indexes;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexes.size() * sizeof(unsigned int), &this->indexes[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/**
 * To be used by renderers, binds the vertex buffer and assigns attribute pointers, then binds the index buffer
 */
void Mesh::bindMesh() {
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glVertexAttribPointer(
        0,                    // attribute 0
        3,                    // size - vec3
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        8 * sizeof(float),    // stride
        (void*)0              // array buffer offset
    );

    glVertexAttribPointer(
        1,                    // attribute 1
        3,                    // size - vec3
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        8 * sizeof(float),    // stride
        (void*)(3 * sizeof(float)) // array buffer offset
    );

    glVertexAttribPointer(
        2,                    // attribute 2
        2,                    // size - vec2
        GL_FLOAT,             // type
        GL_FALSE,             // normalized?
        8 * sizeof(float),    // stride
        (void*)(6 * sizeof(float)) // array buffer offset
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
}

void Mesh::unbindMesh() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::constructVertexBuffer() {
    this->bufferData.clear();

    for (int i = 0; i < this->vertices.size(); i++) { // In theory, same number of normals and uvs as vertices
        this->bufferData.push_back(this->vertices[i].x);
        this->bufferData.push_back(this->vertices[i].y);
        this->bufferData.push_back(this->vertices[i].z);

        if (this->normals.size() > i) {
            this->bufferData.push_back(this->normals[i].x);
            this->bufferData.push_back(this->normals[i].y);
            this->bufferData.push_back(this->normals[i].z);
        } else {
            this->bufferData.push_back(0);
            this->bufferData.push_back(0);
            this->bufferData.push_back(0);
        }

        this->bufferData.push_back(this->uvs[i].x);
        this->bufferData.push_back(this->uvs[i].y);
    }

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(float), &bufferData[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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

namespace PrimitiveMeshes {
    Mesh* generateSphereMesh(int horizontalLines, int verticalLines, float radius) {
        if (horizontalLines < 1 || verticalLines < 1) {
            throw "horizontalLines or verticalLines is less than 1.";
        }

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec2> uvs;
        std::vector<unsigned int> triangles;
        int vertexCount = horizontalLines * verticalLines;
        
        int tris = 0;
        int vertex = -1;

        for (int v = 0; v < verticalLines; v++) {
            for (int h = 0; h < horizontalLines; h++) {
                vertex++;

                vertices.push_back(glm::vec3(
                    (sin(PI * h/horizontalLines) * cos(2 * PI * v/verticalLines) * radius),
                    (sin(PI * h/horizontalLines) * sin(2 * PI * v/verticalLines) * radius),
                    (cos(PI * h/horizontalLines) * radius)
                ));

                uvs.push_back(glm::vec2(
                    v / verticalLines,
                    h / horizontalLines
                ));

                if (h == horizontalLines - 1) { // if last section, next triangles are invalid, skip
                    continue;
                }
                
                if (v == verticalLines - 1) { // if last column, create triangles between first and last vertex columns
                    triangles.push_back(vertex);
                    triangles.push_back(vertex + horizontalLines + 1 - vertexCount);
                    triangles.push_back(vertex + horizontalLines - vertexCount);

                    triangles.push_back(vertex);
                    triangles.push_back(vertex + 1);
                    triangles.push_back(vertex + horizontalLines + 1 - vertexCount);
                } else { // Creates triangles as normal
                    triangles.push_back(vertex);
                    triangles.push_back(vertex + horizontalLines + 1);
                    triangles.push_back(vertex + horizontalLines);

                    triangles.push_back(vertex);
                    triangles.push_back(vertex + 1);
                    triangles.push_back(vertex + horizontalLines + 1);
                }

            }
        }

        unsigned int anchorVertex = horizontalLines - 1;
        unsigned int currentVertex = anchorVertex;

        for (int i = 1; i < verticalLines - 1; i++) {
            currentVertex += horizontalLines;

            triangles.push_back(anchorVertex);
            triangles.push_back(currentVertex + horizontalLines);
            triangles.push_back(currentVertex);
        }

        Mesh* mesh = new Mesh();
        mesh->setVertices(vertices);
        mesh->setUVs(uvs);
        mesh->setIndexes(triangles);
        mesh->recalculateNormals();
        mesh->constructVertexBuffer();
        return mesh;
    }

    Mesh* generateCubeMesh() {

    }
}