#pragma once
#include <iosfwd>
#include <GL/glew.h>
#include <vector>
#include "../../../include/glm/glm.hpp"
#define PI 3.14159265

class Mesh {
public:
    GLuint indexBuffer;
    GLuint vertexBuffer;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indexes;

    Mesh();

    void recalculateNormals();

    void setVertices(std::vector<glm::vec3> vertices);
    void setUVs(std::vector<glm::vec2> uvs);
    void setNormals(std::vector<glm::vec3> normals);
    void setIndexes(std::vector<unsigned int> indexes);
    void constructVertexBuffer();
    void bindMesh();
    void unbindMesh();

    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec2> getUVs();
    std::vector<glm::vec3> getNormals();
    std::vector<unsigned int> getIndexes();
    
private:
    std::vector<float> bufferData;
};

namespace PrimitiveMeshes {
    Mesh* generateSphereMesh(int horizontalLines, int verticalLines, float radius);
    Mesh* generateCubeMesh();
}