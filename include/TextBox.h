//  Copyright 2022 Anthony Tossell
#ifndef INCLUDE_TEXTBOX_H_
#define INCLUDE_TEXTBOX_H_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "IDrawable.h"

class TextBox : public IDrawable {
 private:
    std::string text;
    int width;
    int height;
    int xPos;
    int yPos;
    int fontSize = 48;
    const std::string FONT_PATH = "assets/Connection II-1260.ttf";

    SDL_Surface* textSurface;
    SDL_Texture* textTexture;
    SDL_Renderer* gRenderer;
 public:
    void draw(SDL_Surface* surface);
    std::string getText() const;
    void setText(const std::string& text);
    void setWidth(int w);
    void setHeight(int h);
    void setPosX(int x);
    void setPosY(int y);
    void setRenderer(SDL_Renderer* r);
};

#endif  // INCLUDE_TEXTBOX_H_
