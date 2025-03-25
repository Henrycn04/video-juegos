#include "Entities.h"

Entities::Entities() {

}
Entities::~Entities() {
    
}

void Entities::mover(double deltaTime, int windowWidth, int windowHeight){
    // Mover la imagen
    this->posImg.x += this->velImg.x * deltaTime;
    this->posImg.y += this->velImg.y * deltaTime;

    // Mover el texto
    this->posTxt.x += this->velTxt.x * deltaTime;
    this->posTxt.y += this->velTxt.y * deltaTime;

    // Rebotar la imagen en los bordes de la ventana
    if (this->posImg.x < 0) {
        this->posImg.x = 0;
        this->velImg.x = -this->velImg.x;  // Invertir la velocidad en X
    } else if (this->posImg.x > windowWidth) {
        this->posImg.x = windowWidth;
        this->velImg.x = -this->velImg.x;  // Invertir la velocidad en X
    }

    if (this->posImg.y < 0) {
        this->posImg.y = 0;
        this->velImg.y = -this->velImg.y;  // Invertir la velocidad en Y
    } else if (this->posImg.y > windowHeight) {
        this->posImg.y = windowHeight;
        this->velImg.y = -this->velImg.y;  // Invertir la velocidad en Y
    }

    // Rebotar el texto en los bordes de la ventana
    if (this->posTxt.x < 0) {
        this->posTxt.x = 0;
        this->velTxt.x = -this->velTxt.x;  // Invertir la velocidad en X
    } else if (this->posTxt.x > windowWidth) {
        this->posTxt.x = windowWidth;
        this->velTxt.x = -this->velTxt.x;  // Invertir la velocidad en X
    }

    if (this->posTxt.y < 0) {
        this->posTxt.y = 0;
        this->velTxt.y = -this->velTxt.y;  // Invertir la velocidad en Y
    } else if (this->posTxt.y > windowHeight) {
        this->posTxt.y = windowHeight;
        this->velTxt.y = -this->velTxt.y;  // Invertir la velocidad en Y
    }
}

