#ifndef ENTITIES_H
#define ENTITIES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <../libs/glm/glm.hpp>
#include <iostream>
#include <../libs/sol/sol.hpp>  // Sol2 al final
#include <string>
#include <fstream>
#include <vector>
struct entityData { // ya se usa
    std::string l, p;
    int w, h;
    glm::vec2 pos;
    glm::vec2 vel;
    double a;
};

class Entities {

public:
    Entities();
    ~Entities();

// Imagen
    SDL_Texture* textureImg = nullptr;
    glm::vec2 posImg = glm::vec2();
    glm::vec2 velImg = glm::vec2();
    size_t widthImg = 0;
    size_t heightImg = 0;
    SDL_Rect srcRectImg = {0,0,0,0};
    double angleImg = 0.0;
// Texto
    SDL_Texture* textureTxt = nullptr;
    SDL_Color colorTxt = {0, 0, 0};
    std::string messageTxt = "";
    glm::vec2 posTxt = glm::vec2();
    glm::vec2 velTxt = glm::vec2();
    size_t widthTxt = 0;
    size_t heightTxt = 0;
    double angleTxt = 0.0;
};
#endif