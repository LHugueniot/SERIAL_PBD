#include "Shader.h"

namespace spag{

bool Shader::setMat4f(std::string const & name, 
    Eigen::Matrix4f const & mat){

    // Get MVP shader id
    GLuint matID = glGetUniformLocation(geomGI.m_shaderProgram, name.c_str());
    if (matID){
        // Load VP mat into MVP
        glUniformMatrix4fv(matID, 1, GL_FALSE, mat.data());
        return true;
    }
    std::cout<<"Shader uniform location \""<<name<<"\" does not exist in "<<shaderName<<std::endl;
    return false;
}

/*

bool set1f(std::string const & name, float v0){
	void glUniform1f(GLint location, GLfloat v0);
}
 
bool set2f(std::string const & name, float v0, float v1){
	void glUniform2f(GLint location, GLfloat v0, GLfloat v1);
}
 
bool set3f(std::string const & name, float v0, float v1, float v2){
	void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
}
 
bool set4f(std::string const & name, float v0, float v1, float v2, float v3){
	void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
}
 
bool set1i(std::string const & name, int v0){
	void glUniform1i(GLint location, GLint v0);
}
 
bool set2i(std::string const & name, int v0, int v1){
	void glUniform2i(GLint location, GLint v0, GLint v1);
}
 
bool set3i(std::string const & name, int v0, int v1, int v2){
	void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2);
}
 
bool set4i(std::string const & name, int v0, int v1, int v2, int v3){
	void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
}
 
bool set1ui(std::string const & name, uint v0){
	void glUniform1ui(GLint location, GLuint v0);
}
 
bool set2ui(std::string const & name, uint v0, uint v1){
	void glUniform2ui(GLint location, GLuint v0, GLuint v1);
}
 
bool set3ui(std::string const & name, uint v0, uint v1, uint v2){
	void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2);
}
 
bool set4ui(std::string const & name, uint v0, uint v1, uint v2, uint v3){
	void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
}
 
bool set1fv(std::string const & name, float const * value, size_t count){
	void glUniform1fv(GLint location, GLsizei count, const GLfloat *value);
}
 
bool set2fv(std::string const & name, float const * value, size_t count){
	void glUniform2fv(GLint location, GLsizei count, const GLfloat *value);
}
 
bool set3fv(std::string const & name, float const * value, size_t count){
	void glUniform3fv(GLint location, GLsizei count, const GLfloat *value);
}
 
bool set4fv(std::string const & name, float const * value, size_t count){
	void glUniform4fv(GLint location, GLsizei count, const GLfloat *value);
}
 
bool set1iv(std::string const & name, int const * value, size_t count){
	void glUniform1iv(GLint location, GLsizei count, const GLint *value);
}
 
bool set2iv(std::string const & name, int const * value, size_t count){
	void glUniform2iv(GLint location, GLsizei count, const GLint *value);
}
 
bool set3iv(std::string const & name, int const * value, size_t count){
	void glUniform3iv(GLint location, GLsizei count, const GLint *value);
}
 
bool set4iv(std::string const & name, int const * value, size_t count){
	void glUniform4iv(GLint location, GLsizei count, const GLint *value);
}
 
bool set1uiv(std::string const & name, uint const * value, size_t count){
	void glUniform1uiv(GLint location, GLsizei count, const GLuint *value);
}
 
bool set2uiv(std::string const & name, uint const * value, size_t count){
	void glUniform2uiv(GLint location, GLsizei count, const GLuint *value);
}
 
bool set3uiv(std::string const & name, uint const * value, size_t count){
	void glUniform3uiv(GLint location, GLsizei count, const GLuint *value);
}
 
bool set4uiv(std::string const & name, uint const * value, size_t count){
	void glUniform4uiv(GLint location, GLsizei count, const GLuint *value);
}
 
bool setMatrix2fv(std::string const & name, float const * value, size_t count){
	void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
}
 
bool setMatrix3fv(std::string const & name, float const * value, size_t count){
	void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
}
 
bool setMatrix4fv(std::string const & name, float const * value, size_t count){
	void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
}
 
bool setMatrix2x3fv(std::string const & name, float const * value, size_t count){
	void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
}
 
bool setMatrix3x2fv(std::string const & name, float const * value, size_t count){
	void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
}
 
bool setMatrix2x4fv(std::string const & name, float const * value, size_t count){
	void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
}
 
bool setMatrix4x2fv(std::string const & name, float const * value, size_t count){
	void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
}
 
bool setMatrix3x4fv(std::string const & name, float const * value, size_t count){
	void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
}
 
bool setMatrix4x3fv(std::string const & name, float const * value, size_t count){
	void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
}
*/

}/* namespace spag */