#include "ModelLoader.hpp"

namespace ModelLoader::OBJ {
    Mesh* loadMesh(const char* filepath) {
        std::ifstream file;
        file.open(filepath);
        
        if (!file) {
            std::cerr << "Error: Could not open the file: " << filepath << std::endl;
            return NULL;
        }

        std::string currentObjectName;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;

        for (std::string line; std::getline(file, line); ) {
            std::istringstream in(line);

            std::string command;
            in >> command;

            if (command == "o") {
                in >> currentObjectName;

            } else if (command == "v") {
                float x, y, z;
                in >> x >> y >> z; // TODO understand this syntax
                vertices.push_back(glm::vec3(x, y, z));

            } else if (command == "usemtl") {
                // ignore

            } else if (command == "s") {
                // controls smooth shading, maybe not ignore in the future

            } else if (command == "f") { 
                // Faces, ignore these, we construct them after loading the rest of the info

            } else if (command == "vt") { // vertex texture? This is a UV
                float u, v;
                in >> u >> v;
                uvs.push_back(glm::vec2(u, v));

            } else if (command == "vn") { // vertex normal
                float x, y, z;
                in >> x >> y >> z;
                normals.push_back(glm::vec3(x, y, z));

            }
        }

        file.close();

        std::vector<unsigned int> outIndices;
        std::vector<glm::vec3> outVertices;
        std::vector<glm::vec2> outUvs;
        std::vector<glm::vec3> outNormals;

        VBOIndexer::indexVBO(vertices, uvs, normals, outIndices, outVertices, outUvs, outNormals);
        
        Mesh* mesh = new Mesh();
        
        mesh->setTriangles(outIndices);
        mesh->setVertices(outVertices);
        mesh->setNormals(outNormals);
        mesh->setUVs(outUvs);

        return mesh;
    }
}
