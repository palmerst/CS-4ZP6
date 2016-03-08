#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{

public:

    Camera();

    glm::vec3 pos;
    glm::vec3 origin;
    glm::vec3 up;

    glm::vec3 posToOrigin;

    float inclination;
    float azimuth;

    float radius;

    void update(glm::vec3 newPos);
    void moveOrigin(double deltaInclination, double deltaAzimuth);

};

#endif // CAMERA_H_INCLUDED
