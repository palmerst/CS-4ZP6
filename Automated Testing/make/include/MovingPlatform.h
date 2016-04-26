#ifndef MOVINGPLATFORM_H_INCLUDED
#define MOVINGPLATFORM_H_INCLUDED

#include "KinematicObject.h"
#include <vector>


/*! The MovingPlatform class implements moving platforms.
 */
class MovingPlatform : public KinematicObject
{
    int dir; //!< Direction of movement
    float speed;  //!< Speed of movement
    int destinationNode;  //!< Node that the platform is headed to
    std::vector<cpVect> path;  //!< The path the platform takes

    public:

    //! Creates a new moving platform
    /*!
      \param w Width of platform
      \param speed Speed of platform
      \param path The path the platform takes
      \param thickness The vertical thickness of the platform
    */
    MovingPlatform(float w, float speed, std::vector<cpVect>& path, float thickness = 50.0f);

    //! Updates platform position
    /*!
      \param dt The timestep to move the platform through.
    */
    void update(float dt);

};

#endif // MOVINGPLATFORM_H_INCLUDED
