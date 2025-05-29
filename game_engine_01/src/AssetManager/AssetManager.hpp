#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <unordered_map>

/**
 * @class AssetManager
 * @brief Manages game assets such as textures, fonts, and sounds.
 */
class AssetManager {
private:
    /** @brief Map storing textures, indexed by their string IDs. */
    std::map<std::string, SDL_Texture*> textures;

    /** @brief Map storing fonts, indexed by their string IDs. */
    std::map<std::string, TTF_Font*> fonts;

    /** @brief Unordered map storing sound effects, indexed by their string IDs. */
    std::unordered_map<std::string, Mix_Chunk*> sounds;

public:
    /**
     * @brief Constructs an AssetManager instance.
     */
    AssetManager();

    /**
     * @brief Destroys the AssetManager and frees all loaded assets.
     */
    ~AssetManager();

    /**
     * @brief Clears all loaded assets from memory.
     */
    void ClearAssets();

    /**
     * @brief Loads and adds a texture to the manager.
     * @param renderer The SDL renderer used to create the texture.
     * @param textureId The unique identifier for the texture.
     * @param filePath The file path to the texture image.
     */
    void AddTexture(SDL_Renderer* renderer, const std::string& textureId, const std::string& filePath);

    /**
     * @brief Retrieves a texture by its ID.
     * @param textureId The unique identifier of the texture.
     * @return Pointer to the SDL_Texture, or nullptr if not found.
     */
    SDL_Texture* GetTexture(const std::string& textureId);

    /**
     * @brief Loads and adds a font to the manager.
     * @param fontId The unique identifier for the font.
     * @param filePath The file path to the font file.
     * @param fontSize The size of the font.
     */
    void AddFont(const std::string& fontId, const std::string& filePath, int fontSize);

    /**
     * @brief Retrieves a font by its ID.
     * @param fontId The unique identifier of the font.
     * @return Pointer to the TTF_Font, or nullptr if not found.
     */
    TTF_Font* GetFont(const std::string& fontId);

    /**
     * @brief Loads and adds a sound effect to the manager.
     * @param soundId The unique identifier for the sound.
     * @param filePath The file path to the sound file.
     */
    void AddSound(const std::string& soundId, const std::string& filePath);

    /**
     * @brief Retrieves a sound effect by its ID.
     * @param soundId The unique identifier of the sound.
     * @return Pointer to the Mix_Chunk, or nullptr if not found.
     */
    Mix_Chunk* GetSound(const std::string& soundId);
};

#endif