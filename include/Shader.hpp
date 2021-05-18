#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
class Shader
{
private:
    GLuint type;
    bool _usable;
    const GLuint _id;
    std::string filepath;
    std::string getTypeString();
    void compileShaderWithError(GLuint shader);

public:
    Shader(std::string filepath, GLuint shadertype);
    ~Shader();
    void del();
    bool usable() const;
    const GLuint id() const;
};
