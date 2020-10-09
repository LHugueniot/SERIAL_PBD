#include "SoftBodyGeometry.h"

namespace spag{

void initGeomBufferObjects(SoftBodyGeometryGI & geomGI){
    // Gen VBO
    glGenBuffers(1, &geomGI.m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, geomGI.m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 geomGI.m_vertexPositionsSize * sizeof(float),
                 &geomGI.m_vertexPositions[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    // Gen IBO
    glGenBuffers(1, &geomGI.m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geomGI.m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                 geomGI.m_faceIndicesSize * sizeof(uint), 
                 &geomGI.m_faceIndices[0], GL_STATIC_DRAW);

    glDisableVertexAttribArray(0);
}

void updateBufferObjects(SoftBodyGeometryGI & geomGI){

    glBindBuffer(GL_ARRAY_BUFFER, geomGI.m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 geomGI.m_vertexPositionsSize * sizeof(float),
                 &geomGI.m_vertexPositions[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geomGI.m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                 geomGI.m_faceIndicesSize * sizeof(uint), 
                 &geomGI.m_faceIndices[0], GL_STATIC_DRAW);

    glDisableVertexAttribArray(0);
}

void drawGeom(SoftBodyGeometryGI const & geomGI, 
              Eigen::Matrix4f const & viewProjMat){

    auto & shader = *(geomGI.m_shader);
    // Use our shader
    shader.bind();

    // Load VP mat into MVP
    shader.setMat4f("MVP", &viewProjMat);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, geomGI.m_vbo);
    glVertexAttribPointer(
        0,        // attribute
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void*)0  // array buffer offset
    );

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geomGI.m_ibo);

    // Draw the triangles !
    glDrawElements(
        GL_TRIANGLES,             // mode
        geomGI.m_faceIndicesSize, // count
        GL_UNSIGNED_SHORT,        // type
        (void*)0                  // element array buffer offset
    );

    glDisableVertexAttribArray(0);

    shader.unBind();
}

} /* namespace spag */