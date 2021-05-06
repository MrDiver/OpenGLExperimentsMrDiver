#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
class Shader
{
private:
    GLuint type;
    std::string filepath;
    std::string getTypeString();
    void compileShaderWithError(GLuint shader);

public:
    const GLuint id;
    Shader(std::string fn, GLuint shadertype);
    ~Shader();
};
