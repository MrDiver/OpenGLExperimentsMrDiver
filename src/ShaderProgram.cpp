#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <ShaderProgram.hpp>
#include <Shader.hpp>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram()
    : id(glCreateProgram())
{
}

ShaderProgram::ShaderProgram(const std::vector<Shader> &s)
    : id(glCreateProgram())
{
    for(auto i=s.begin(); i!=s.end(); ++i){
        this->attach(*i);
    }
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(this->id);
}

void ShaderProgram::attach(const Shader &shader)
{
    if(shader.usable())
        glAttachShader(this->id, shader.id());
    else
        throw std::runtime_error("ShaderProgram::ERROR::attach: Shader was already deleted");
}

void ShaderProgram::link()
{
    this->linkShaderProgramWithError(this->id);
}

void ShaderProgram::use()
{
    glUseProgram(this->id);
}

void ShaderProgram::linkShaderProgramWithError(const GLuint program)
{
    glLinkProgram(program);
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::LINK\n"
                  << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

// int
void ShaderProgram::setUniform1i(const std::string &name, GLint v)
{
    GLuint location = glGetUniformLocation(this->id, name.c_str());
    glUniform1i(location, v);
}

void ShaderProgram::setUniform2i(const std::string &name, GLint v0, GLint v1)
{
    GLuint location = glGetUniformLocation(this->id, name.c_str());
    glUniform2i(location, v0, v1);
}

void ShaderProgram::setUniform3i(const std::string &name, GLint v0, GLint v1, GLint v2)
{
    GLuint location = glGetUniformLocation(this->id, name.c_str());
    glUniform3i(location, v0, v1, v2);
}

void ShaderProgram::setUniform4i(const std::string &name, GLint v0, GLint v1, GLint v2, GLint v3)
{
    GLuint location = glGetUniformLocation(this->id, name.c_str());
    glUniform4i(location, v0, v1, v2, v3);
}
// unsigned int
void ShaderProgram::setUniform1ui(const std::string &name, GLuint v)
{
    GLuint location = glGetUniformLocation(this->id, name.c_str());
    glUniform1ui(location, v);
}

void ShaderProgram::setUniform2ui(const std::string &name, GLuint v0, GLuint v1)
{
    GLuint location = glGetUniformLocation(this->id, name.c_str());
    glUniform2ui(location, v0, v1);
}

void ShaderProgram::setUniform3ui(const std::string &name, GLuint v0, GLuint v1, GLuint v2)
{
    GLuint location = glGetUniformLocation(this->id, name.c_str());
    glUniform3ui(location, v0, v1, v2);
}

void ShaderProgram::setUniform4ui(const std::string &name, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
{
    GLuint location = glGetUniformLocation(this->id, name.c_str());
    glUniform4ui(location, v0, v1, v2, v3);
}
// Floats
void ShaderProgram::setUniform1f(const std::string &name, GLfloat v)
{
    GLuint location = glGetUniformLocation(this->id, name.c_str());
    glUniform1f(location, v);
}

void ShaderProgram::setUniform2f(const std::string &name, GLfloat v0, GLfloat v1)
{
    GLuint location = glGetUniformLocation(this->id, name.c_str());
    glUniform2f(location, v0, v1);
}

void ShaderProgram::setUniform3f(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2)
{
    GLuint location = glGetUniformLocation(this->id, name.c_str());
    glUniform3f(location, v0, v1, v2);
}

void ShaderProgram::setUniform4f(const std::string &name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    GLuint location = glGetUniformLocation(this->id, name.c_str());
    glUniform4f(location, v0, v1, v2, v3);
}

void ShaderProgram::setUniformMatrix(const std::string& name, glm::mat4 v, bool transpose)
{
    GLuint location = glGetUniformLocation(this->id, name.c_str());
    glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(v));
}
