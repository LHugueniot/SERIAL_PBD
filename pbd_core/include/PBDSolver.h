#ifndef SPAG_PBD_SOLVER_H
#define SPAG_PBD_SOLVER_H

#include "Common.h"
#include "SoftBodyGeometry.h"
#include "PhysicalAttributes.h"

namespace spag{

template<typename T>
T length3f(T * a, T * b){
    return T(sqrt(a[0]*b[0] + a[1]*b[1] + a[2]*b[2]));
}
template<typename T>
T length3f(T * a){
    return T(sqrt(a[0]*a[0] + a[1]*a[1] + a[2]*a[2]));
}

void advanceStep(SoftBodyGeometry & geom,         // soft body geom to solve on
                 PhysicalAttributes & pa,         // physical attributes
                 float ts                         // time step
                 );

} /* namespace spag */

#endif /* SPAG_PBD_SOLVER_H */