#ifndef SOUNDCOMPONENT_HPP
#define SOUNDCOMPONENT_HPP

#include <string>

struct SoundComponent {
    std::string soundId;
    int volume;
    int loops;
    bool isPlaying;
    bool active;
    bool autoPlay;
    
    SoundComponent(const std::string& soundId = "none", int volume = 128, int loops = -1, bool autoPlay = true, bool active = true) {
        this->soundId = soundId;
        this->volume = volume;
        this->loops = loops;
        this->isPlaying = false;
        this->active = active;
        this->autoPlay = autoPlay;
    }
};

#endif