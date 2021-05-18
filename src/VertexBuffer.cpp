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

VertexBuffer::VertexBuffer(const std::vector<float> v, const GLenum usage)
:num(1)
{
    this->ids = new GLuint[num];
    glGenBuffers(num, this->ids);
    //Bind Data
    this->bind(0);
    this->bindData(v, usage);
}

VertexBuffer::VertexBuffer(const std::vector<std::vector<float>> v, const GLenum usage)
:num(v.size())
{
    if(num < 1) throw std::runtime_error("VertexBuffer::ERROR::Constructor: Length of the given Vector is smaller than 1");
    this->ids = new GLuint[num];
    glGenBuffers(num, this->ids);
    //Bind Data
    uint8_t buffer = 0;
    for(auto i=v.begin(); i!=v.end();++i){
        this->bind(buffer);
        this->bindData(*i, usage);
    }
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
