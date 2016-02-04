#include "SoundStore.h"

SoundStore::SoundStore(){};

Sound* SoundStore::add(std::string path){

    std::map<std::string, Sound*>::iterator it = soundMap.find(path);
    Sound* sound;

    if(it == soundMap.end()){
        sound = new Sound(path);
        soundMap.insert(std::pair<std::string, Sound*>(path, sound));
    } else {
        sound = it->second;
    }

    return sound;

}

Sound* SoundStore::get(std::string path){

    return soundMap.find(path)->second;

}
