#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Projection{
private:
    glm::mat4 projection;
    float fov,width,height,nearplane,farplane;
public:
    Projection();
    ~Projection();
};
