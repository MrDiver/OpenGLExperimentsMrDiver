#pragma once
#include <Projection.hpp>
#define GLM_SWIZZLE_XYZW
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
private:
    glm::vec3 pos, dir, right, up;
    glm::mat4 mview;
    void update();
public:
    Camera(Projection projection);
    Camera(Projection projection, glm::vec3 position);
    Camera(Projection projection, glm::vec3 position, glm::vec3 direction);
    ~Camera();
    void setPosition(glm::vec3 pos);
    void setDirection(glm::vec3 dir);
    void lookAt(glm::vec3 target);
    void moveLocal(glm::vec3 offset);
    void moveGlobal(glm::vec3 offset);
    glm::vec3 position();
    glm::vec3 direction();


    glm::mat4 view(); //returns projection * view
    glm::mat4 viewOnly();

    Projection projection;
//     float yaw();
//     float pitch();
//     float roll();
//     void setYaw(float yaw);
//     void setPitch(float pitch);
//     void setRoll(float roll);
};
