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
        std::list<glm::vec3> vertices;
        std::list<unsigned int> triangles;

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
                int a, b, c;
                in >> a >> b >> c;
                triangles.push_back(a);
                triangles.push_back(b);
                triangles.push_back(c);
            }
        }

        file.close();
    }
}
