#pragma once
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
class Texture2D{
private:
    GLuint id;
    int _width, _height, _nrChannels;
public:
    Texture2D(const char* filename,
                     const GLenum image_type=GL_RGB,
                     const GLenum wrap_s=GL_REPEAT,
                     const GLenum wrap_t=GL_REPEAT,
                     const GLenum min_filter=GL_NEAREST,
                     const GLenum mag_filter=GL_LINEAR);
    ~Texture2D();
    void bind() const;
    void bindTo(const uint8_t textureIdx) const;
    int width() const;
    int height() const;
    int channels() const;
};
