#pragma once
#include<vector>
#include<glm/matrix.hpp>
class Shader;

class ShaderProgram
{
private:
    void linkShaderProgramWithError(GLuint program);

public:
    const GLuint id;
    void attach(const Shader &shader);
    void link();
    void use();
    // Uniform setters
    // unsigned int
    void setUniform1i(const std::string &name, GLint v);
    void setUniform2i(const std::string &name, GLint v0, GLint v1);
    void setUniform3i(const std::string &name, GLint v0, GLint v1, GLint v2);
    void setUniform4i(const std::string &name, GLint v0, GLint v1, GLint v2, GLint v3);
    // int
    void setUniform1ui(const std::string &name, GLuint v);
    void setUniform2ui(const std::string &name, GLuint v0, GLuint v1);
    void setUniform3ui(const std::string &name, GLuint v0, GLuint v1, GLuint v2);
    void setUniform4ui(const std::string &name, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
    // Floats
    void setUniform1f(const std::string &name, GLfloat v);
    void setUniform2f(const std::string &name, GLfloat v0, GLfloat v1);
    void setUniform3f(const std::string &name, GLfloat v0, GLfloat v1, GLfloat  v2);
    void setUniform4f(const std::string &name, GLfloat v0, GLfloat v1, GLfloat  v2, GLfloat v3);
    // Vectors / Matrices
    // Floats
    void setUniformMatrix(const std::string &name, glm::mat4 v, bool transpose = GL_FALSE);

    //Constructor Destructor
    ShaderProgram();
    ShaderProgram(const std::vector<Shader> &s);
    ~ShaderProgram();
};
