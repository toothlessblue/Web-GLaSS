#include "ModelLoader.hpp"
#include <iostream>

std::map<const char*, Mesh*, Utils::String::cmp_str> ModelLoader::_meshCache;

void ModelLoader::_addMeshToCache(const char* key, Mesh* mesh) {
    ModelLoader::_meshCache.insert(std::pair<const char*, Mesh*>(key, mesh));
}

bool ModelLoader::_isCached(const char* key) {
    return ModelLoader::_meshCache.count(key) > 0;
}

Mesh* ModelLoader::_getMeshFromCache(const char* key) {
    return ModelLoader::_meshCache[key];
}

// Note: Breaks if format of obj file not properly configured, 
// this is not a robust loader
Mesh* ModelLoader::OBJ::loadMesh(const char* filepath) {
    if (!ModelLoader::_isCached(filepath)) {
        std::ifstream file;
        file.open(filepath);
        
        if (!file) {
            std::cerr << "Error: Could not open the file: " << filepath << std::endl;
            return NULL;
        }

        std::string currentObjectName;
        std::vector<glm::vec3> uniqueVertices;
        std::vector<glm::vec3> uniqueNormals;
        std::vector<glm::vec2> uniqueUvs;

        std::vector<unsigned int> vertexIndices;
        std::vector<unsigned int> uvIndices;
        std::vector<unsigned int> normalIndices;

        for (std::string line; std::getline(file, line); ) {
            std::istringstream in(line);

            std::string command;
            in >> command;

            if (command == "o") {
                in >> currentObjectName;

            } else if (command == "v") {
                float x, y, z;
                in >> x >> y >> z;
                uniqueVertices.push_back(glm::vec3(x, y, z));

            } else if (command == "usemtl") {
                // ignore

            } else if (command == "s") {
                // controls smooth shading, maybe not ignore in the future

            } else if (command == "f") { // face info
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                if (matches != 9){
                    printf("File can't be read OBJLoader :( Make sure you export with UVs and normals, and have triangulate mesh checked");
                    return NULL;
                }

                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices    .push_back(uvIndex[0]);
                uvIndices    .push_back(uvIndex[1]);
                uvIndices    .push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);

            } else if (command == "vt") { // vertex texture? This is a UV
                float u, v;
                in >> u >> v;
                uniqueUvs.push_back(glm::vec2(u, v));

            } else if (command == "vn") { // vertex normal
                float x, y, z;
                in >> x >> y >> z;
                uniqueNormals.push_back(glm::vec3(x, y, z));

            }
        }

        file.close();

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;

        for (unsigned int i = 0; i < vertexIndices.size(); i++) {
            vertices.push_back(uniqueVertices[vertexIndices[i] - 1]);
            normals.push_back(uniqueNormals[normalIndices[i] - 1]);
            uvs.push_back(uniqueUvs[uvIndices[i] - 1]);
        }

        std::vector<unsigned int> outIndices;
        std::vector<glm::vec3> outVertices;
        std::vector<glm::vec2> outUvs;
        std::vector<glm::vec3> outNormals;

        VBOIndexer::indexVBO(vertices, uvs, normals, outIndices, outVertices, outUvs, outNormals);
        
        Mesh* mesh = new Mesh();
        
        mesh->setIndexes(outIndices);
        mesh->setVertices(outVertices);
        mesh->setUVs(outUvs);
        mesh->recalculateNormals();
        mesh->constructVertexBuffer();

        return mesh; // TODO fix bug with textures and cached mesh objects
        ModelLoader::_addMeshToCache(filepath, mesh);
    }

    return ModelLoader::_getMeshFromCache(filepath);
}

Mesh* ModelLoader::WebModel::loadMesh(const char* filepath) {
    throw "Not implemented";
}