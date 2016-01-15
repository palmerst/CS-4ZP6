#ifndef SOUND_H
#define SOUND_H

#include "include/AL/alut.h"


/*! The Sound class loads and stores sound data.
 */
class Sound{


    ALuint audioBuffer;    //!< Binding id for sound data storage.
	ALuint audioSource;    //!< Binding id for position, velocity, etc. of sound source.

    public:


        //! Sound constructor
        /*!
          \param path Path to the sound file that should be loaded.
          \param loop Non-zero if the sound should be played as an infinite loop.
        */
        Sound(char* path, int loop);
        ~Sound();       //!< Sound destructor
        void play();    //!< Plays the sound data contained in the class.

};

#endif // SOUND_H