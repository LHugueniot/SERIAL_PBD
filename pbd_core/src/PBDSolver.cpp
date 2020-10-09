#include "PBDSolver.h"

namespace spag{

void advanceStep(SoftBodyGeometry & geom,         // soft body geom to solve on
                 PhysicalAttributes & pa,         // physical attributes
                 float ts                         // time step
                 ){

    float dt = 1.f/ts; // delta time

    float * projPos = new float [geom.m_verticesNum * 3];

    for(size_t vi=0; vi<geom.m_verticesNum; vi++){ // Loop over vertices as indices (vi)
        for(Dim d=X; d!=Z; d++){                   // Loop over dimensions as indices (d)

            size_t idx = vi * 3 + d;
            geom.m_vertexVelocities[idx] = geom.m_vertexVelocities[idx] * 
                                    geom.m_inverseMass[vi] *
                                    pa.m_damp * 
                                    dt;

            projPos[idx] = geom.m_vertexPositions[idx] +
                           geom.m_vertexVelocities[idx] *
                           dt;
        }
    }

    float kprime= 1.f - pow(1.0f-0.5f, 1.f/(float)pa.m_iters);

    for(size_t i = 0; i < pa.m_iters; i++){

        // Solve for distance constraints
        for(size_t dc=0; dc<geom.m_distanceConstraintsNum; dc++){ // Loop over distance constraints
            size_t dcIdx1 = geom.m_distanceConstraints[dc * 2];       // Distance constraint 1
            size_t dcIdx2 = geom.m_distanceConstraints[dc * 2 + 1];   // Distance constraint 2

            size_t v1Idx = dcIdx1 * 3;
            size_t v2Idx = dcIdx2 * 3;

            float dir[3] = {
                projPos[v1Idx]     - projPos[v2Idx],
                projPos[v1Idx + 1] - projPos[v2Idx + 1],
                projPos[v1Idx + 2] - projPos[v2Idx + 2]
            };

            float dcLen = length3f(&dir[0]);

            float invMass1 = geom.m_inverseMass[dcIdx1];
            float invMass2 = geom.m_inverseMass[dcIdx2];
            float w = invMass1 + invMass2;

            if(w == 0 || dcLen) continue;

            float dcRestLen = geom.m_distanceConstraintRestLength[dc];
            float invDcLen = 1.f/dcLen;
            float invW = 1.f/w;

            for(Dim d=X; d<=Z; d++){
                projPos[v1Idx + d] -= (invMass1 * invW) * 
                                      (dcLen - dcRestLen) * 
                                      (dir[d] * invDcLen) * 
                                      kprime;

                projPos[v2Idx + d] += (invMass2 * invW) * 
                                      (dcLen - dcRestLen) * 
                                      (dir[d] * invDcLen) * 
                                      kprime;
            }
        }
        // precompute values
        static float third = 1.f/3.f;
        static float two_third = 2.f/3.f;
        // Solve for bending constraints
        for(size_t bc=0; bc<geom.m_bendingConstraintsNum; bc++){ // Loop over distance constraints
            size_t bcIdx1 = geom.m_bendingConstraints[bc * 3];        // Bending constraint 1
            size_t bcIdx2 = geom.m_bendingConstraints[bc * 3 + 1];    // Bending constraint 2
            size_t bcIdx3 = geom.m_bendingConstraints[bc * 3 + 2];    // Bending constraint 3

            size_t v1Idx = bcIdx1 * 3;
            size_t v2Idx = bcIdx2 * 3;
            size_t v3Idx = bcIdx3 * 3;

            float centroid[3] = {
                projPos[v2Idx]      * two_third - (projPos[v1Idx]     + projPos[v3Idx]    ) * third,
                projPos[v2Idx + 1]  * two_third - (projPos[v1Idx + 1] + projPos[v3Idx + 1]) * third,
                projPos[v2Idx + 2]  * two_third - (projPos[v1Idx + 2] + projPos[v3Idx + 2]) * third
            };

            float bcLen = length3f(&centroid[0]);

            float invMass1 = geom.m_inverseMass[bcIdx1];
            float invMass2 = geom.m_inverseMass[bcIdx2];
            float invMass3 = geom.m_inverseMass[bcIdx3];
            float w = invMass1 + invMass2 + invMass3;

            if(w == 0 || bcLen) continue;

            float invBcLen = 1.f/bcLen;
            float magniDiff = 1.f - (0.5f + geom.m_bendingConstraintRestLength[bc]) * invBcLen;
            float invW = 1.f/w;

            for(Dim d=X; d<=Z; d++){
                projPos[v1Idx + d] -= (2 * invMass1 * invW) * 
                                      centroid[d] * 
                                      magniDiff;

                projPos[v2Idx + d] += (-4 * invMass2 * invW) * 
                                      centroid[d] * 
                                      magniDiff;

                projPos[v3Idx + d] += (2 * invMass3 * invW) * 
                                      centroid[d] * 
                                      magniDiff;
            }
        }
    }
    for(size_t vi=0; vi<geom.m_verticesNum; vi++){ // Loop over vertices as indices (vi)
        for(Dim d=X; d!=Z; d++){                   // Loop over dimensions as indices (d)
            size_t idx = vi * 3 + d;

            geom.m_vertexVelocities[idx] = projPos[idx] - geom.m_vertexPositions[idx] * dt;
            geom.m_vertexPositions[idx] = projPos[idx];
        }
    }
    delete[] projPos;
}

} /* namespace spag */