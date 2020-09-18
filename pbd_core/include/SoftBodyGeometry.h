#ifndef SPAG_SOFT_BODY_GEOMETRY_H
#define SPAG_SOFT_BODY_GEOMETRY_H

#include "Common.h"
#include "Shader.h"

namespace spag{

static float GRAV_DEFAULT[3] = {0.f, 0.98f, 0.f};

struct PhysicalAttributes{

    PhysicalAttributes() = delete;

    PhysicalAttributes(float _grav[3] = GRAV_DEFAULT,
                       float _timeStep = .24f, 
                       uint _iterations = 16,
                       float _damp = 0.99f) :
    m_ts(_timeStep),
    m_iters(_iterations),
    m_damp(_damp) {
        for(int i=0; i<3; i++)
            m_grav[i] = _grav[i];
    }

    // Gravity
    float m_grav[3];

    // Time step
    float m_ts;

    // Number of iterations
    uint m_iters;

    float m_damp;
};

struct SoftBodyGeometry{
    SoftBodyGeometry();

    // Total number of conceptual vertices
    uint m_verticesNum;

    float * m_vertexPositions;
    // Total size of m_vertexPositions (m_verticesNum * 3)
    uint m_vertexPositionsSize;
    // Buffer of velocities of vertices data
    float * m_vertexVelocities;
    // Total size of m_vertexVelocities (equal to m_vertexPositionsSize)
    uint m_vertexVelocitiesSize;
    /* 
        Buffer of positions of vertices data packed like so:
        [ x1,y1,z1, x2,y2,z2, x3,y3,z3, x4,y4,z4]  // Vertex buffer
          \______/  \______/  \______/  \______/
           vertex1   vertex2   vertex3   vertex4   // Conceptual vertices
        To access vertex data per dimension:
            0 <= Dim < 2
            0 <= vertexi < m_verticesNum                
            vert_dim = m_vertexPositions[vertexi * 3 + Dim]

        e.g:
            float vert2_y = m_vertexPositions[2 * 3 + Y]
    */

    // Buffer of inverse mass of vertices data
    // Store only inverse of mass as mass is only
    // used in inverse form in PBD equations
    float * m_inverseMass;
    // Total size of m_vertexVelocities (equal to m_verticesNum)
    uint m_inverseMassSize;

    // Buffer containing distance constraint vertex indices
    uint * m_distanceConstraints;
    // Total size of distance constraints buffer 
    // (m_distanceConstraintsNum * 2)
    uint m_distanceConstraintsSize;
    // Buffer containing distance constraint rest lengths 
    // (size is m_distanceConstraintsNum)
    float * m_distanceConstraintRestLength;
    // Number of conceptual distance constraints
    uint m_distanceConstraintsNum;
    /* 
        Buffer containing "conceptual" vertex index
        [(0,1), (0,2), (2,1)]  // Conceptual vertex index
          \_/    \_/    \_/
          dc1    dc2    dc3    // Conceptual distance constraints
        To access each distance constraint vertex data per dimension:
            0 <= vn < 1                             // first or second vertex
            0 <= dcn < m_distanceConstraintsNum     // distance constraint number
            dcn_vn = m_distanceConstraints[dcn * 2 + vn]
            dcn_vn_dim = m_vertexPositions[dci_vn * 3 + Dim]
        e.g:
            uint dc3_v2 = m_distanceConstraints[3 * 2 + 1] //second vertex of distance constraint 3
            float dc3_v2_y = m_vertexPositions[2 * 3 + Y]
    */

    // Buffer containing distance constraint vertex indices
    uint * m_bendingConstraints;
    // Total size of bending constraints buffer 
    // (m_bendingConstraintsNum * 3)
    uint m_bendingConstraintsSize;
    // Buffer containing bending constraint rest lengths 
    // (size is m_distanceConstraintsNum)
    float * m_bendingConstraintRestLength;
    // Number of conceptual bending constraints
    uint m_bendingConstraintsNum;
};


struct SoftBodyGeometryGraphicalInterface : SoftBodyGeometry{

    SoftBodyGeometryGraphicalInterface(){}

    ~SoftBodyGeometryGraphicalInterface(){}
    // Vertex Array Object
    GLuint m_vao;

    // Vertex Buffer Object
    GLuint m_vbo;

    // Index Buffer Object
    GLuint m_ibo;

    uint m_faceIndicesSize;
    uint * m_faceIndices;

    
    std::shared_ptr<Shader> m_shader;
};

using SoftBodyGeometryGI = SoftBodyGeometryGraphicalInterface;

void initGeomBufferObjects(SoftBodyGeometryGI & geomGI);

void updateBufferObjects(SoftBodyGeometryGI & geomGI);

void drawGeom(SoftBodyGeometryGI const & geomGI, 
              Eigen::Matrix4f const & viewProjMat);

} /* namespace spag */

#endif /* SPAG_SOFT_BODY_GEOMETRY_H */