#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP
#include <SDL2/SDL.h>
#include <string>

/**
 * @brief Component that handles sprite rendering properties
 * 
 * Stores texture information, dimensions, and rendering state for an entity.
 */
struct SpriteComponent {
    SDL_Rect srcRect;          ///< Source rectangle for sprite sheet cropping
    std::string textureId;     ///< ID of the texture resource to use
    int width;                ///< Width of the sprite in pixels
    int height;               ///< Height of the sprite in pixels
    SDL_RendererFlip flip;    ///< Current flip state (none, horizontal, vertical)
    bool active;              ///< Whether the sprite should be rendered

    /**
     * @brief Construct a new Sprite Component object
     * 
     * @param textureId ID of the texture to use (default: "none")
     * @param width Sprite width in pixels (default: 0)
     * @param height Sprite height in pixels (default: 0)
     * @param srcRectX X position in source texture (default: 0)
     * @param srcRectY Y position in source texture (default: 0)
     * @param active Whether sprite is initially active (default: true)
     */
    SpriteComponent(const std::string& textureId = "none", 
                   int width = 0, 
                   int height = 0, 
                   int srcRectX = 0, 
                   int srcRectY = 0, 
                   bool active = true)
    {
        this->textureId = textureId;
        this->width = width;
        this->height = height;
        this->srcRect = { srcRectX, srcRectY, width, height };
        this->flip = SDL_FLIP_NONE;
        this->active = active;
    }
};
#endif // SPRITECOMPONENT_HPP