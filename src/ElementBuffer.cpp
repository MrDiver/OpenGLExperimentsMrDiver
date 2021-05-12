#include <ElementBuffer.hpp>
#include <stdexcept>

ElementBuffer::ElementBuffer(const uint8_t num)
:num(num)
{
    if(num < 1) throw std::runtime_error("ElementBuffer::ERROR::Constructor: Value num is less than one");
    this->ids = new GLuint[num];
    glGenBuffers(num, this->ids);
}

ElementBuffer::~ElementBuffer()
{
    delete[] this->ids;
}

void ElementBuffer::bind(const uint8_t idx) const
{
    if (idx < 0 || idx >= this->num) throw std::runtime_error("ElementBuffer::ERROR::bind: Index out of range");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ids[idx]);
}


void ElementBuffer::bindData(const std::vector<int> &data, const GLenum usage) const
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(int), data.data(), usage);
}
