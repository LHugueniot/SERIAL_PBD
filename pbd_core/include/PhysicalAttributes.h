#ifndef SPAG_PHYSICAL_ATRIBUTES_H
#define SPAG_PHYSICAL_ATRIBUTES_H

#include "Common.h"

namespace spag{

static float GRAV_DEFAULT[3] = {0.f, -.980665f, 0.f};

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

} /* namespace spag */

#endif /* SPAG_PHYSICAL_ATRIBUTES_H */