#pragma once
#include <GL/glew.h>
#include <vector>
#include "../../../include/glm/glm.hpp"

class Mesh {
public:
    Mesh();

    void recalculateNormals();

    void setVertices(std::vector<glm::vec3> vertices);
    void setUVs(std::vector<glm::vec2> uvs);
    void setNormals(std::vector<glm::vec3> normals);
    void setIndexes(std::vector<unsigned int> indexes);

    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec2> getUVs();
    std::vector<glm::vec3> getNormals();
    std::vector<unsigned int> getIndexes();

    void draw();
private:
    GLuint vertexArray;

    GLuint vertexBuffer;
    GLuint uvBuffer;
    GLuint indexesBuffer;
    GLuint normalsBuffer;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indexes;
};