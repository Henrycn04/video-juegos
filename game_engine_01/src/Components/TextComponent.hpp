#ifndef TEXT_COMPONENT_HPP
#define TEXT_COMPONENT_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

/**
 * @brief Component that handles text rendering properties
 * 
 * Stores text content, font information, and rendering properties for text display.
 */
struct TextComponent {
    std::string text;     ///< The text string to be displayed
    std::string fontId;   ///< ID of the font resource to use
    SDL_Color color;     ///< Color of the text (RGBA)
    int width;          ///< Width of the rendered text in pixels
    int height;         ///< Height of the rendered text in pixels

    /**
     * @brief Construct a new Text Component object
     * 
     * @param text The text content (default: "")
     * @param fontId ID of the font to use (default: "")
     * @param r Red component (0-255) (default: 0)
     * @param g Green component (0-255) (default: 0)
     * @param b Blue component (0-255) (default: 0)
     * @param a Alpha (transparency) component (0-255) (default: 0)
     */
    TextComponent(const std::string& text = "", 
                 const std::string& fontId = "", 
                 u_char r = 0, 
                 u_char g = 0, 
                 u_char b = 0, 
                 u_char a = 0) {
        this->text = text;
        this->fontId = fontId;
        this->color.r = r;
        this->color.g = g;
        this->color.b = b;
        this->color.a = a;
        this->width = 0;
        this->height = 0;
    }
};

#endif // TEXT_COMPONENT_HPP