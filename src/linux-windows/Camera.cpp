#include "Camera.h"
#include <iostream>

Camera::Camera()
{
    init();
}

Camera::~Camera()
{

}

void Camera::init()
{
    cameraPosition = glm::vec3(1.0f, 1.0f, -1.0f);
    cameraTarget = glm::vec3(1.0f, 1.0f, 0.0f);
    cameraDirection = glm::normalize(cameraPosition - cameraTarget);
    up = glm::vec3(0.0f, -1.0f, 0.0f);
    cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
    view = glm::lookAt(cameraPosition, 
                       cameraTarget, 
                       cameraUp);
    // view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
    //                    glm::vec3(0.0f, 0.0f, 0.0f), 
    //                    glm::vec3(0.0f, 1.0f, 0.0f));
}

void Camera::moveCamera(float _x, float _y, float _z)
{
    cameraPosition.x += _x;
    cameraPosition.y += _y;
    cameraPosition.z += _z;
    view = glm::lookAt(cameraPosition, 
                       cameraTarget, 
                       cameraUp);
}

glm::mat4 Camera::getView()
{
    return view;
}
