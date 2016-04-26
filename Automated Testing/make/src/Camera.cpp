#include "Camera.h"


Camera::Camera()
{
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    zoom = 1.0f;
}

void Camera::zoomIn(){
    if(zoom <= 1.0f){
        zoom = 1.0f;
        return;
    }

    zoom /= 1.03f;
}

void Camera::zoomOut(){
    if(zoom >= 5.0f){
        zoom = 5.0f;
        return;
    }

    zoom *= 1.03f;
}
