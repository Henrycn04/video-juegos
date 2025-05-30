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
 * with SoundComponents. Supports game pause/resume functionality.
 */
class SoundSystem : public System {
private:
    /** @brief Indicates if the sound system is globally paused. */
    bool systemPaused = false;

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
     * Does not process sounds when system is paused.
     */
    void Update(std::unique_ptr<AssetManager>& assetManager) {
        // Si el sistema está pausado, no procesar nuevos sonidos
        if (systemPaused) {
            return;
        }

        std::vector<Entity> entities = GetSystemEntities();
        for (auto& entity : entities) {
            auto& sound = entity.GetComponent<SoundComponent>();
            if (!sound.active) {
                continue;
            }

            // Auto-reproducir sonidos marcados para autoPlay
            if (sound.autoPlay && !sound.isPlaying && !sound.isPaused) {
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
     * Updates the isPlaying flag and assigns audio channel for control.
     */
    void PlaySound(std::unique_ptr<AssetManager>& assetManager, SoundComponent& sound) {
        if (sound.soundId == "none" || !sound.active) {
            return;
        }

        Mix_Chunk* chunk = assetManager->GetSound(sound.soundId);
        if (chunk != nullptr) {
            Mix_VolumeChunk(chunk, sound.volume);
            int channel = Mix_PlayChannel(-1, chunk, sound.loops);
            if (channel != -1) {
                sound.channel = channel;
                sound.isPlaying = true;
                sound.isPaused = false;
            }
        }
    }

    /**
     * @brief Stops a sound playback.
     * @param sound Reference to the SoundComponent to stop.
     *
     * Halts the sound on its assigned channel and resets playback state.
     */
    void StopSound(SoundComponent& sound) {
        if (sound.channel != -1) {
            Mix_HaltChannel(sound.channel);
            sound.channel = -1;
        }
        sound.isPlaying = false;
        sound.isPaused = false;
    }

    /**
     * @brief Pauses sound playback for a specific sound.
     * @param sound Reference to the SoundComponent to pause.
     *
     * Pauses the sound on its assigned channel if it's currently playing.
     */
    void PauseSound(SoundComponent& sound) {
        if (sound.isPlaying && sound.channel != -1 && !sound.isPaused) {
            Mix_Pause(sound.channel);
            sound.isPaused = true;
        }
    }

    /**
     * @brief Resumes paused sound playback for a specific sound.
     * @param sound Reference to the SoundComponent to resume.
     *
     * Resumes the sound on its assigned channel if it was paused.
     */
    void ResumeSound(SoundComponent& sound) {
        if (sound.isPlaying && sound.channel != -1 && sound.isPaused) {
            Mix_Resume(sound.channel);
            sound.isPaused = false;
        }
    }

    /**
     * @brief Pauses all currently playing sounds when game is paused.
     *
     * Called when the game enters pause state. Iterates through all
     * sound entities and pauses those that are currently playing.
     * Sets system to paused state to prevent new sounds from playing.
     */
    void OnGamePaused() {
        systemPaused = true;
        std::vector<Entity> entities = GetSystemEntities();

        for (auto& entity : entities) {
            auto& sound = entity.GetComponent<SoundComponent>();
            if (sound.active && sound.isPlaying && !sound.isPaused) {
                PauseSound(sound);
                std::cout << "[SOUND] Pausando sonido: " << sound.soundId << std::endl;
            }
        }
    }

    /**
     * @brief Resumes all paused sounds when game is resumed.
     *
     * Called when the game exits pause state. Iterates through all
     * sound entities and resumes those that were paused during game pause.
     * Sets system to active state to allow new sounds to play.
     */
    void OnGameResumed() {
        systemPaused = false;
        std::vector<Entity> entities = GetSystemEntities();

        for (auto& entity : entities) {
            auto& sound = entity.GetComponent<SoundComponent>();
            if (sound.active && sound.isPlaying && sound.isPaused) {
                ResumeSound(sound);
                std::cout << "[SOUND] Reanudando sonido: " << sound.soundId << std::endl;
            }
        }
    }

    /**
     * @brief Gets the current pause state of the sound system.
     * @return true if the system is paused, false otherwise.
     */
    bool IsSystemPaused() const {
        return systemPaused;
    }
};

#endif