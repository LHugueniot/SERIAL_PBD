#ifndef SPAG_SOFT_BODY_GEOMETRY_H
#define SPAG_SOFT_BODY_GEOMETRY_H

#include "Common.h"
#include "Shader.h"
#include "Drawable.h"
#include "Geometry.h"

namespace spag{

struct SoftBodyGeometry : Geometry{
    SoftBodyGeometry();

    // Buffer of velocities of vertices data
    float * m_vertexVelocities;
    // Total size of m_vertexVelocities (equal to m_vertexPositionsSize)
    uint m_vertexVelocitiesSize;

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


struct SoftBodyGeometryGraphicalInterface : 
    public SoftBodyGeometry,
    public Drawable{

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
};

using SoftBodyGeometryGI = SoftBodyGeometryGraphicalInterface;

void initGeomBufferObjects(SoftBodyGeometryGI & geomGI);

void updateBufferObjects(SoftBodyGeometryGI & geomGI);

void drawGeom(SoftBodyGeometryGI const & geomGI, 
              Eigen::Matrix4f const & viewProjMat);

} /* namespace spag */

#endif /* SPAG_SOFT_BODY_GEOMETRY_H */

/*
template<template<typename...> Containter>
struct SoftBody{
    template<template<typename...> Containter2>
    SoftBody(SoftBody<Container2> const & other){
        m_data_1 = other.m_data_1;
        m_data_2 = other.m_data_2;
    }

    Contrainer<float> m_data_1;
    Contrainer<uint> m_data_1;
};

using HostSoftBody = SoftBody<std::vector>;
using DevicdeSoftBody = SoftBody<thrust::device_vector>;

void do(HostSoftBody sb);
void do(DeviceSoftBody sb);
*/
