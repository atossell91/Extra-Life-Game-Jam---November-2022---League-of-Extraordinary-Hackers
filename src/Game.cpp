#include "../include/Game.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <vector>
#include <iostream>
#include <Algorithm>

#include "../include/IDrawable.h"
#include "../include/IOverlappable.h"
#include "../include/GameRectangle.h"

void Game::start() {
    init();
    run();
    close();
}

void Game::init() {
    //  These should be in if statements (possibly nested)
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Boxes",SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
}

void Game::draw() {
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,125,125,125));
    for (auto d : drawables) {
        d->draw(surface);
    }
    SDL_UpdateWindowSurface(window);
}

void Game::run() {
    GameRectangle* r1 = new GameRectangle();
    GameRectangle* r2 = new GameRectangle();
    GameRectangle* r3 = new GameRectangle();
    GameRectangle* r4 = new GameRectangle();
    r2->setX(100);
    r2->setY(100);

    r3->setX(247);
    r3->setY(201);

    r4->setColour(0, 0, 255);
    r4->setX(100);
    r4->setY(300);

    drawables.push_back(static_cast<IDrawable*>(r1));
    drawables.push_back(static_cast<IDrawable*>(r2));
    drawables.push_back(static_cast<IDrawable*>(r3));
    drawables.push_back(static_cast<IDrawable*>(r4));

    physicals.push_back(static_cast<IOverlappable*>(r1));
    physicals.push_back(static_cast<IOverlappable*>(r2));
    physicals.push_back(static_cast<IOverlappable*>(r3));

    nonPhysicals.push_back(static_cast<IOverlappable*>(r4));
    nonPhysicals.push_back(static_cast<IOverlappable*>(r1));

    r1->setPhysicalsList(&physicals);
    //r2->setPhysicalsList(&physicals);

    r1->setNonPhysicalsList(&nonPhysicals);
    r4->setNonPhysicalsList(&nonPhysicals);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
    int count = 0;
        while (SDL_PollEvent(&e)) {
            //  Event handlers go in here
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                int amt = 10;
                const Uint8* state = SDL_GetKeyboardState(NULL);
                if (state[SDL_SCANCODE_UP]) {
                    r1->moveY(-amt);
                }
                if (state[SDL_SCANCODE_DOWN]) {
                    r1->moveY(amt);
                }
                if (state[SDL_SCANCODE_LEFT]) {
                    r1->moveX(-amt);
                }
                if (state[SDL_SCANCODE_RIGHT]) {
                    r1->moveX(amt);
                }
            }
        }
        draw();
    }
}

void Game::close() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}