#pragma once
#include <stdint.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>


class VertexBuffer{
private:
    const uint8_t num;
    GLuint* ids{};

public:
    VertexBuffer(const uint8_t num = 1);
    ~VertexBuffer();
    void bind(const uint8_t idx = 0) const;
    void bindData(const std::vector<float> &data, const GLenum usage = GL_STATIC_DRAW) const; //  GL_STATIC_DRAW,  GL_DYNAMIC_DRAW
};
