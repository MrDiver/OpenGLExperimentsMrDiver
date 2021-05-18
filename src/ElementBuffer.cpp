#include <ElementBuffer.hpp>
#include <stdexcept>

ElementBuffer::ElementBuffer(const uint8_t num)
:num(num)
{
    if(num < 1) throw std::runtime_error("ElementBuffer::ERROR::Constructor: Value num is less than one");
    this->ids = new GLuint[num];
    glGenBuffers(num, this->ids);
}


ElementBuffer::ElementBuffer(const std::vector<int> v, const GLenum usage)
:num(1)
{
    this->ids = new GLuint[num];
    glGenBuffers(num, this->ids);
    //Bind Data
    this->bind(0);
    this->bindData(v, usage);
}

ElementBuffer::ElementBuffer(const std::vector<std::vector<int>> v, const GLenum usage)
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
