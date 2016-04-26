#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

/*! The Camera class controls the view of the stage.
 */
class Camera
{

public:

    //! Camera constructor.
    Camera();

    glm::vec3 up;  //!< The up vector.

    float zoom;  //!< Current zoom level.

    //! Zoom the view in.
    void zoomIn();

    //! Zoom the view out.
    void zoomOut();

};

#endif // CAMERA_H_INCLUDED
