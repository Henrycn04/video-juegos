#ifndef SOUNDSYSTEM_HPP
#define SOUNDSYSTEM_HPP

#include <SDL2/SDL_mixer.h>
#include <vector>
#include <memory>
#include "../AssetManager/AssetManager.hpp"
#include "../Components/SoundComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class SoundSystem
 * @brief System for managing sound playback in the ECS framework.
 *
 * Handles playing, stopping, pausing, and resuming sounds for entities
 * with SoundComponents.
 */
class SoundSystem : public System {
public:
    /**
     * @brief Constructs a SoundSystem and requires SoundComponent for entities.
     */
    SoundSystem() {
        RequireComponent<SoundComponent>();
    }

    /**
     * @brief Updates the sound system state and handles auto-play sounds.
     * @param assetManager Reference to the asset manager for sound loading.
     *
     * Iterates through all entities with SoundComponents and automatically
     * plays sounds marked for autoPlay that aren't currently playing.
     */
    void Update(std::unique_ptr<AssetManager>& assetManager) {
        std::vector<Entity> entities = GetSystemEntities();
        for (auto& entity : entities) {
            auto& sound = entity.GetComponent<SoundComponent>();

            if (!sound.active) {
                continue;
            }
            // Auto-reproducir sonidos marcados para autoPlay
            if (sound.autoPlay && !sound.isPlaying) {
                PlaySound(assetManager, sound);
            }
        }
    }
    
    /**
     * @brief Plays a sound from the SoundComponent.
     * @param assetManager Reference to the asset manager for sound loading.
     * @param sound Reference to the SoundComponent containing sound properties.
     *
     * Loads and plays the specified sound with configured volume and loop settings.
     * Updates the isPlaying flag based on playback success.
     */
    void PlaySound(std::unique_ptr<AssetManager>& assetManager, SoundComponent& sound) {
        if (sound.soundId == "none" || !sound.active) {
            return;
        }
        
        Mix_Chunk* chunk = assetManager->GetSound(sound.soundId);
        if (chunk != nullptr) {
            Mix_VolumeChunk(chunk, sound.volume);
            int channel = Mix_PlayChannel(-1, chunk, sound.loops);
            sound.isPlaying = (channel != -1);
        }
    }
    
    /**
     * @brief Stops a sound playback.
     * @param sound Reference to the SoundComponent to stop.

     */
    void StopSound(SoundComponent& sound) {
        sound.isPlaying = false;
        // Nota: Para detener un sonido específico necesitarías trackear el canal
    }
    
    /**
     * @brief Pauses sound playback.
     * @param sound Reference to the SoundComponent to pause.

     */
    void PauseSound(SoundComponent& sound) {
        if (sound.isPlaying) {
            Mix_Pause(-1); // Pausa todos los canales, idealmente trackearias el canal específico
        }
    }
    
    /**
     * @brief Resumes paused sound playback.
     * @param sound Reference to the SoundComponent to resume.

     */
    void ResumeSound(SoundComponent& sound) {
        if (!sound.isPlaying) {
            Mix_Resume(-1); // Reanuda todos los canales
        }
    }
};

#endif