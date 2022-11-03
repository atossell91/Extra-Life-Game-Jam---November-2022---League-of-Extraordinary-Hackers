#include "../include/Game.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <vector>
#include <iostream>
#include <Algorithm>
#include <thread>
#include <chrono>

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
    bg_surface = SDL_LoadBMP("assets/map/map.bmp");
}

void Game::draw() {
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,125,125,125));

    SDL_BlitSurface(bg_surface, NULL, surface, NULL);

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

    r1->setWidth(27);
    r1->setHeight(30);
    
    r1->loadSpriteFiles({
        "assets/person/person-small-0.bmp",
        "assets/person/person-small-1.bmp",
        "assets/person/person-small-2.bmp"
    });

    GameRectangle* a = new GameRectangle();
    a->setColour(125,125,0);
    a->setX(250);

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
    drawables.push_back(static_cast<IDrawable*>(a));

    physicals.push_back(static_cast<IOverlappable*>(r1));
    physicals.push_back(static_cast<IOverlappable*>(r2));
    physicals.push_back(static_cast<IOverlappable*>(r3));
    physicals.push_back(static_cast<IOverlappable*>(a));

    nonPhysicals.push_back(static_cast<IOverlappable*>(r4));
    nonPhysicals.push_back(static_cast<IOverlappable*>(r1));

    r1->setPhysicalsList(&physicals);
    a->setPhysicalsList(&physicals);
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
        a->moveY(3);
        draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    }
}

void Game::close() {
    SDL_FreeSurface(bg_surface);
    bg_surface = NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();
}