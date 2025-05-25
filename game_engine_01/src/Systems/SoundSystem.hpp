#ifndef SOUNDSYSTEM_HPP
#define SOUNDSYSTEM_HPP

#include <SDL2/SDL_mixer.h>
#include <vector>
#include <memory>
#include "../AssetManager/AssetManager.hpp"
#include "../Components/SoundComponent.hpp"
#include "../ECS/ECS.hpp"

class SoundSystem : public System {
public:
    SoundSystem() {
        RequireComponent<SoundComponent>();
    }

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
    
    void StopSound(SoundComponent& sound) {
        sound.isPlaying = false;
        // Nota: Para detener un sonido específico necesitarías trackear el canal
    }
    
    void PauseSound(SoundComponent& sound) {
        if (sound.isPlaying) {
            Mix_Pause(-1); // Pausa todos los canales, idealmente trackearias el canal específico
        }
    }
    
    void ResumeSound(SoundComponent& sound) {
        if (!sound.isPlaying) {
            Mix_Resume(-1); // Reanuda todos los canales
        }
    }
};

#endif