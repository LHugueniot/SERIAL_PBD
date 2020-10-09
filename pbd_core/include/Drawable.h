#ifndef SPAG_DRAWABLE_H
#define SPAG_DRAWABLE_H

#include "Common.h"

namespace spag{

struct Drawable{

    virtual ~Drawable() = default;

    // Force override
    virtual void draw(Eigen::Matrix4f & cameraMat) = 0;

    // Shader to be used
    std::shared_ptr<Shader> m_shader;
};

} /* namespace spag */

#endif /* SPAG_SHADER_H */