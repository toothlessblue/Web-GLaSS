#pragma once
#include <iosfwd>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "VBOIndexer.hpp"
#include <vector>

#include "../../../include/glm/glm.hpp"
#include "../Mesh/Mesh.hpp"
#include "../Utils/StringUtils.hpp"

namespace ModelLoader {
    extern std::map<const char*, Mesh*, Utils::String::cmp_str> _meshCache;

    void _addMeshToCache(const char* key, Mesh* mesh);
    Mesh* _getMeshFromCache(const char* key);
    bool _isCached(const char* key);

    namespace OBJ { // OBJs can be used for quick prototyping
        Mesh* loadMesh(const char* filepath);
    }

    namespace WebModel {
        // TODO convert all OBJs to easy to load WebModels
        //   Copy OBJ loader and have it export meshes as .webmodel files

        // Custom format similar to OBJ that ONLY contains vertices, uvs, and normals
        // OBJs should be processed into WebModels for quicker loading, as it only has
        //   one index buffer and therefore doesn't need to be processed before being rendered
        Mesh* loadMesh(const char* filepath);
    }
}