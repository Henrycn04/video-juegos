#ifndef SOUNDCOMPONENT_HPP
#define SOUNDCOMPONENT_HPP

#include <string>

/**
 * @struct SoundComponent
 * @brief Component for managing sound properties for an entity in the ECS.
 */
struct SoundComponent {
    /** @brief Identifier for the sound asset. */
    std::string soundId;

    /** @brief Volume level of the sound (0 to 128). */
    int volume;

    /** @brief Number of times to loop the sound (-1 for infinite). */
    int loops;

    /** @brief Indicates whether the sound is currently playing. */
    bool isPlaying;

    /** @brief Indicates whether the sound component is active. */
    bool active;

    /** @brief Indicates whether the sound should play automatically. */
    bool autoPlay;

    /**
     * @brief Constructs a SoundComponent with specified parameters.
     * @param soundId Identifier for the sound asset (default: "none").
     * @param volume Volume level of the sound (default: 128).
     * @param loops Number of loops for the sound (-1 for infinite, default: -1).
     * @param autoPlay Whether the sound should play automatically (default: true).
     * @param active Whether the sound component is active (default: true).
     */
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