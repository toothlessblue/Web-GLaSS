#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>

#include "../../../include/glm/glm.hpp"
#include "../Mesh/Mesh.hpp"

namespace ModelLoader {
    namespace OBJ { // OBJs can be used for quick prototyping
        Mesh* loadMesh(char* filepath);
    }

    namespace WebModel { // TODO implement
        // Custom format similar to OBJ that ONLY contains vertices, uvs, and normals
        // OBJs should be processed into WebModels for quicker loading, as it only has
        //    one index buffer and therefore doesn't need to be processed before being rendered
        Mesh* loadMesh(char* filepath);
    }
}