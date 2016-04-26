#ifndef SOUNDSTORE_H_INCLUDED
#define SOUNDSTORE_H_INCLUDED

#include <map>
#include "Sound.h"


/*! The SoundStore class acts as a storage class for loaded sounds.
 */
class SoundStore
{

private:

    std::map<std::string, Sound*> soundMap;  //!< Map translates sound file name to stored data

public:

    //! Constructor
    SoundStore();

    //! Adds a new sound to the store:  if not in the store, it loads and stores;  if already present, it does nothing
    /*!
      \param path Path to sound file
    */
    Sound* add(std::string path);

    //! Retrieves gpu data from the store
    /*!
      \param path Path to sound file
    */
    Sound* get(std::string path);

};

#endif // SOUNDSTORE_H_INCLUDED
