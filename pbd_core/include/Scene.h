#ifndef SPAG_SCENE_H
#define SPAG_SCENE_H

#include "Common.h"
#include "Shader.h"
#include "Camera.h"
#include "ImportGeometry.h"
#include "SoftBodyGeometry.h"
#include "PhysicalAttributes.h"


namespace spag{

// TEMPORARY

class Geometry;
class RigidBodyGeometry;

struct Scene{

    std::shared_ptr<PhysicalAttributes> m_pa;

    // Current scene camera
    std::shared_ptr<Camera> m_currentCamera;

    // Store pointers to cameras
    std::vector<std::shared_ptr<Camera>> m_cameras;

    // Store pointers to shared shaders (no need to compile twice!)
    std::vector<std::shared_ptr<Shader>> m_sharedShaders;

    // Store pointers to all Geometry base class
    std::vector<std::shared_ptr<Geometry>> m_geoms;

    // Store pointers to SBGs
    std::vector<std::shared_ptr<SoftBodyGeometry>> m_SBGs;

    // Store pointers to RBGs
    std::vector<std::shared_ptr<RigidBodyGeometry>> m_RBGs;
};

}

#endif /* SPAG_SCENE_H */