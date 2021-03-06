#ifndef SOUND_H
#define SOUND_H

#include "AL/alut.h"
#include <string>


/*! The Sound class loads and stores sound data.
 */
class Sound
{
    ALuint audioBuffer;    //!< Binding id for sound data storage.
    ALuint audioSource;    //!< Binding id for position, velocity, etc. of sound source.

    bool loaded;    //!< Flag specifies if sound is loaded.

public:


    //! Sound constructor
    /*!
      \param path Path to the sound file that should be loaded.
    */
    Sound(std::string path);
    ~Sound();       //!< Sound destructor
    void play(int loop = 0);    //!< Plays the sound data contained in the class.
    void stop();    //!< Stops playing sound.
};

#endif // SOUND_H
