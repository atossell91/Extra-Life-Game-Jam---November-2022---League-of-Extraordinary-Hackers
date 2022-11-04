//  Copyright 2022 Anthony Tossell
#include "../include/TextBox.h"

void TextBox::draw(SDL_Surface* surface) {
    TTF_Font* font = TTF_OpenFont(FONT_PATH.c_str(), fontSize);
    SDL_Color Black = {0, 0, 0};
    textSurface = TTF_RenderText_Solid(font, text.c_str(), Black);
    SDL_Rect rect;
    rect.h = height;
    rect.w = width;
    rect.x = xPos;
    rect.y = yPos;
    SDL_BlitSurface(textSurface, NULL, surface, &rect);
}
std::string TextBox::getText() const {
    return text;
}

void TextBox::setText(const std::string& text) {
    this->text = text;
}

void TextBox::setWidth(int w) {
    width = w;
}

void TextBox::setHeight(int h) {
    height = h;
}

void TextBox::setPosX(int x) {
    xPos = x;
}

void TextBox::setPosY(int y) {
    yPos = y;
}

void TextBox::setRenderer(SDL_Renderer* renderer) {
    gRenderer = renderer;
}
