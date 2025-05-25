#include "AssetManager.hpp"
#include <iostream>
AssetManager::AssetManager() {
    std::cout<< "[AssetManager] Se ejecuta constructor" << std::endl;
}
AssetManager::~AssetManager() {
    std::cout<< "[AssetManager] Se ejecuta destructor" << std::endl;

}
void AssetManager::ClearAssets() {
    for (auto& texture : textures) {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();

    for (auto& font : fonts) {
        TTF_CloseFont(font.second);
    }
    fonts.clear();

    for (auto& sound : sounds) {
        Mix_FreeChunk(sound.second);
    }
    sounds.clear();
}
void AssetManager::AddTexture(SDL_Renderer* renderer, const std::string& textureId, const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr) {
        std::cerr << "[AssetManager] Error al cargar la textura: " << IMG_GetError() << std::endl;
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) {
        std::cerr << "[AssetManager] Error al crear la textura: " << SDL_GetError() << std::endl;
        return;
    }
    textures.emplace(textureId, texture);
}
SDL_Texture* AssetManager::GetTexture(const std::string& textureId) {
    return textures[textureId];
}

void AssetManager::AddFont(const std::string& fontId, const std::string& filePath, int fontSize){
    TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
    if (font == NULL) {
        std::cerr << "[AssetManager] Error al cargar la fuente: " << TTF_GetError() << std::endl;
        return;
    }
    fonts.emplace(fontId, font);
}
TTF_Font* AssetManager::GetFont(const std::string& fontId){
    return fonts[fontId];
}
void AssetManager::AddSound(const std::string& soundId, const std::string& filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
    if (sound == nullptr) {
        std::cerr << "[AssetManager] Error al cargar el sonido: " << Mix_GetError() << std::endl;
        return;
    }
    sounds.emplace(soundId, sound);
}

Mix_Chunk* AssetManager::GetSound(const std::string& soundId) {
    return sounds[soundId];
}