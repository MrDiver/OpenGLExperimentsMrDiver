#include <VertexArray.hpp>
#include <stdexcept>
VertexArray::VertexArray(const uint8_t num)
:num(num)
{
    if(num < 1) throw std::runtime_error("VertexArray::ERROR::Constructor: Value num is less than one");
    this->ids = new GLuint[num];
    glGenVertexArrays(num, this->ids);
}

VertexArray::~VertexArray()
{
    delete[] this->ids;
}

void VertexArray::bind(const uint8_t idx) const
{
    if (idx < 0 || idx >= this->num) throw std::runtime_error("VertexArray::ERROR::bind: Index out of range");
    glBindVertexArray(this->ids[idx]);
}

void VertexArray::set(const uint8_t pointer, GLuint64 size, GLuint64 shift, GLuint64 start) const
{
    glVertexAttribPointer(pointer, size, GL_FLOAT, GL_FALSE, shift * sizeof(float),  (void *)(start*sizeof(float)));
}

void VertexArray::enable(const uint8_t pointer) const
{
    glEnableVertexAttribArray(pointer);
}

void VertexArray::disable(const uint8_t pointer) const
{
    glDisableVertexAttribArray(pointer);
}
