#include <Texture2D.hpp>
#include <stb_image.hpp>
#include <stdexcept>

Texture2D::Texture2D(const char* filename,
                     const GLenum image_type,
                     const GLenum wrap_s,
                     const GLenum wrap_t,
                     const GLenum min_filter,
                     const GLenum mag_filter)
{
    glGenTextures(1, &this->id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

    unsigned char *data = stbi_load(filename,&this->_width,&this->_height,&this->_nrChannels,0);
    if(data){
        GLenum type;
        if(this->_nrChannels == 1){
            type = GL_RED;
        }else if (this->_nrChannels == 3){
            type = GL_RGB;
        }else if (this->_nrChannels == 4){
            type = GL_RGBA;
        }else{
            throw std::runtime_error("Texture2D::ERROR::Constructor: Image has wrong number of channels");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, image_type, this->_width, this->_height, 0, type, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }else{
        throw std::runtime_error("Texture2D::ERROR::Constructor: Error loading File (File not found)");
    }
    stbi_image_free(data);
}

Texture2D::~Texture2D()
{

}

void Texture2D::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture2D::bindTo(const uint8_t textureIdx) const
{
    if(textureIdx < 0 || textureIdx > 31) throw std::runtime_error("Texture2D::ERROR::bindTo: Texture index out of bounds. Index must be in range 0-31");
    glActiveTexture(GL_TEXTURE0+textureIdx);
    this->bind();
}

int Texture2D::width() const
{
    return this->_width;
}

int Texture2D::height() const
{
    return this->_height;
}

int Texture2D::channels() const
{
    return this->_nrChannels;
}

