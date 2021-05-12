#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class VertexArray{
private:
    const uint8_t num;
    GLuint* ids{};
public:
    VertexArray(const uint8_t num = 1);
    ~VertexArray();
    void bind(const uint8_t idx = 0) const;
    void enable(const uint8_t pointer) const;
    void disable(const uint8_t pointer) const;
    void set(const uint8_t pointer, GLuint64 size, GLuint64 shift, GLuint64 start) const;
};
