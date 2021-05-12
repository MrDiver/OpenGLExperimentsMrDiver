#pragma once
#include <stdint.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>


class ElementBuffer{
private:
    const uint8_t num;
    GLuint* ids{};

public:
    ElementBuffer(const uint8_t num = 1);
    ~ElementBuffer();
    void bind(const uint8_t idx = 0) const;
    void bindData(const std::vector<int> &data, const GLenum usage = GL_STATIC_DRAW) const; //  GL_STATIC_DRAW,  GL_DYNAMIC_DRAW
};
