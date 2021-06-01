#include <Camera.hpp>

Camera::Camera(Projection projection)
:Camera::Camera(projection,glm::vec3(0.0f,0.0f,0.0f)){}

Camera::Camera(Projection projection, glm::vec3 position)
:Camera::Camera(projection,position,glm::vec3(0.0f,0.0f,-1.0f)){}

Camera::Camera(Projection projection, glm::vec3 position, glm::vec3 direction)
:pos(position), dir(direction), projection(projection){
    update();
}

Camera::~Camera(){};

void Camera::update(){
    // Calculate View Matrix
    this->right = glm::normalize(glm::cross(glm::vec3(0.0f,1.0f,0.0f), this->dir)); //need to create a constant
    this->up = glm::cross(this->dir, this->right);
    this->mview = glm::lookAt(this->pos,this->pos-this->dir,this->up);
}

void Camera::setPosition(glm::vec3 pos)
{
    this->pos = pos;
    this->update();
}

void Camera::setDirection(glm::vec3 dir){
    this->dir = glm::normalize(dir);
    this->update();
}

void Camera::lookAt(glm::vec3 target){
    this->dir = glm::normalize(this->pos - target);
    this->update();
}

void Camera::moveLocal(glm::vec3 offset){
    this->pos += offset.x*this->right + offset.y*this->up + offset.z * this->dir;
    update();
}

void Camera::moveGlobal(glm::vec3 offset){
    this->pos += offset;
    update();
}

glm::vec3 Camera::position(){
    return this->pos;
}

glm::vec3 Camera::direction(){
    return this->dir;
}

glm::mat4 Camera::view()
{
    return this->mview;
}

glm::mat4 Camera::viewOnly()
{
    return this->mview;
}
