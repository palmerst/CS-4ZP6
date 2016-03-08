#ifndef SOUNDSTORE_H_INCLUDED
#define SOUNDSTORE_H_INCLUDED

#include <map>
#include "Sound.h"

class SoundStore
{

private:

    std::map<std::string, Sound*> soundMap;

public:

    SoundStore();

    Sound* add(std::string path);
    Sound* get(std::string path);

};

#endif // SOUNDSTORE_H_INCLUDED
