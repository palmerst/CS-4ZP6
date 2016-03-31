#include "Camera.h"

#define PI 3.141596f

Camera::Camera()
{

    pos = glm::vec3(0.0f);
    origin = glm::vec3(0.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    posToOrigin = glm::vec3(1.0f, 0.0f, 0.0f);

    zoom = 1.0f;

    inclination = PI/2;
    azimuth = 0;

}

void Camera::update(glm::vec3 newPos)
{

    pos = newPos;
    origin = pos + posToOrigin;

}

void Camera::moveOrigin(double deltaInclination, double deltaAzimuth)
{

    inclination += deltaInclination;
    azimuth += deltaAzimuth;

    if(inclination > 99.0*PI/100.0)
        inclination = 99.0*PI/100.0;
    if(inclination < PI/100.0)
        inclination = PI/100.0;

    posToOrigin[0] = sin(inclination)*cos(azimuth);
    posToOrigin[1] = cos(inclination);
    posToOrigin[2] = sin(inclination)*sin(azimuth);

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
