#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP
#include <SDL2/SDL.h>
#include <string>

struct SpriteComponent {
    SDL_Rect srcRect;
    std::string textureId;
    int width;
    int height;
    SDL_RendererFlip flip;
    bool active;

    SpriteComponent(const std::string& textureId = "none", int width = 0, int height = 0, int srcRectX = 0, int srcRectY = 0, bool active = true)
        {
            this->textureId = textureId;
            this->width = width;
            this->height = height;
            this->srcRect = { srcRectX, srcRectY, width, height };
            this->flip = SDL_FLIP_NONE;
            this->active = active;
    }
};
#endif