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

    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), &this->vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::setUVs(std::vector<glm::vec2> uvs) {
    this->uvs = uvs;

    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->uvs.size() * sizeof(glm::vec2), &this->uvs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::setNormals(std::vector<glm::vec3> normals) {
    this->normals = normals;

    glBindBuffer(GL_ARRAY_BUFFER, this->normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), &this->normals[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::setIndexes(std::vector<unsigned int> indexes) {
    if (indexes.size() % 3 != 0) {
        std::cerr << "Size of indexes is not a multiple of 3, this may be malformed." << std::endl;
    }

    this->indexes = indexes;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexes.size() * sizeof(unsigned int), &this->indexes[0], GL_STATIC_DRAW);
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
        return mesh;
    }

    Mesh* generateCubeMesh() {

    }
}