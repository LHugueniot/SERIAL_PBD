#ifndef SPAG_IMPORT_GEOMETRY_H
#define SPAG_IMPORT_GEOMETRY_H

#include "Common.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace spag{

aiScene const * importScene(std::string const & scenePath);

std::vector<aiMesh*> getMeshesFromScene(aiScene * scene);

bool getMeshData(aiMesh const & mesh,  // Assume mesh is exclusively triangulated
                 std::vector<float> & vertexPositions, 
                 std::vector<uint> & edgeIndices,
                 std::vector<uint> & triFaceIndices);

} /* namespace spag */

#endif /* SPAG_IMPORT_GEOMETRY_H */