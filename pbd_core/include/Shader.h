#ifndef SPAG_SHADER_H
#define SPAG_SHADER_H

#include "Common.h"

namespace spag{

class Shader{
    std::string shaderName;
    Gluint m_shaderProgram;

    bool setMat4f(std::string const & name, 
                  Eigen::Matrix4f const & mat);
    bool setMat4f(std::string const & name, 
                  Eigen::Matrix4f const & mat);
}

} /* namespace spag */

#endif /* SPAG_SHADER_H */