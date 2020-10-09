#ifndef SPAG_GEOMETRY_H
#define SPAG_GEOMETRY_H

#include "Common.h"

namespace spag{

struct Geometry{
    // Geometry name
    std::string m_name;
    // Total number of conceptual vertices
    uint m_verticesNum;
    // Vertex data buffer
    float * m_vertexPositions;
    // Total size of m_vertexPositions (m_verticesNum * 3)
    uint m_vertexPositionsSize;
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
};

} /* namespace spag */

#endif /* SPAG_GEOMETRY_H */