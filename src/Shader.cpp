#include <Shader.hpp>
#include <fstream>
#include <iostream>

Shader::Shader(std::string filepath, GLuint shadertype)
    : _usable(true),_id(glCreateShader(shadertype))
{
    this->type = shadertype;
    this->filepath = filepath;
    std::ifstream ifs(filepath);
    if (!ifs.is_open())
    {
#ifdef DEBUG
        std::cerr << "ERROR::SHADER::" << getTypeString() << "::READ" << filepath << std::endl;
#endif
        exit(EXIT_FAILURE);
    }
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    ifs.close();
    const char *charstring = content.c_str();
    glShaderSource(this->_id, 1, &charstring, NULL);
    compileShaderWithError(this->_id);
}

Shader::~Shader()
{
    if(this->usable()) glDeleteShader(this->_id);
}

std::string Shader::getTypeString()
{
    std::string ref;
    switch (this->type)
    {
    case GL_VERTEX_SHADER:
        ref = "VERTEX";
        break;
    case GL_FRAGMENT_SHADER:
        ref = "FRAGMENT";
        break;
    case GL_GEOMETRY_SHADER:
        ref = "GEOMETRY";
        break;
    default:
        ref = "NONE";
        break;
    }
    return ref;
}

void Shader::compileShaderWithError(GLuint shader)
{
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::" << getTypeString() << "::COMPILATION\n"
                  << this->filepath << "\n"
                  << infoLog << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
#ifdef DEBUG
    std::cout << "SUCCESS::SHADER::" << getTypeString() << "::COMPILATION "
              << this->filepath << std::endl;
#endif
}

void Shader::del(){
    this->_usable = false;
    glDeleteShader(this->_id);
}

bool Shader::usable() const{
    return this->_usable;
}

const GLuint Shader::id() const{
    return this->_id;
}
