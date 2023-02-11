#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
    private:
        glm::vec3 cameraPosition;
        glm::vec3 cameraTarget;
        glm::vec3 cameraDirection;
        glm::vec3 up;
        glm::vec3 cameraRight;
        glm::vec3 cameraUp;
        glm::mat4 view;
    public:
        Camera();
        ~Camera();
        void init();
        void moveCamera(float _x, float _y, float _z);
        glm::mat4 getView();
};

#endif