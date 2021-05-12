#include <VertexBuffer.hpp>
#include <stdexcept>
#include <iostream>

VertexBuffer::VertexBuffer(const uint8_t num)
:num(num)
{
    if(num < 1) throw std::runtime_error("VertexBuffer::ERROR::Constructor: Value num is less than one");
    this->ids = new GLuint[num];
    glGenBuffers(num, this->ids);
}

VertexBuffer::~VertexBuffer()
{
    delete[] this->ids;
}

void VertexBuffer::bind(const uint8_t idx) const
{
    if (idx < 0 || idx >= this->num) throw std::runtime_error("VertexBuffer::ERROR::bind: Index out of range");
    glBindBuffer(GL_ARRAY_BUFFER, this->ids[idx]);
}


void VertexBuffer::bindData(const std::vector<float> &data, const GLenum usage) const
{
    glBufferData(GL_ARRAY_BUFFER, data.size() *sizeof(float), data.data(), usage);
}
