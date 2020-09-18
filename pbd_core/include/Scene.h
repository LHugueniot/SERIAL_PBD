#ifndef SPAG_SCENE_H
#define SPAG_SCENE_H

#include "Common.h"
#include "Shader.h"
#include "ImportGeometry.h"
#include "SoftBodyGeometry.h"

namespace spag{


// TEMPORARY
class Camera;
class Geometry;
class RigidBodyGeometry;

struct Scene{

	std::vector<std::shared_ptr<Camera>> m_cameras;

	// 
	std::shared_ptr<Camera> m_currentCamera;

    // 
    std::vector<std::shared_ptr<Shader>> m_sharedShaders;

    // Store pointers to all Geometry base class
    std::vector<std::shared_ptr<Geometry>> m_geoms;

    // Store pointers to SBGs
    std::vector<std::shared_ptr<SoftBodyGeometry>> m_SBGs;

    // Store pointers to RBGs
    std::vector<std::shared_ptr<RigidBodyGeometry>> m_SBGs;
};

}

#endif /* SPAG_SCENE_H */