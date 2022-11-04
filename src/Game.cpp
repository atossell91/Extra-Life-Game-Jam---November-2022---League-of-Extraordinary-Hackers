#include "../include/Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

#include "../include/IDrawable.h"
#include "../include/IOverlappable.h"
#include "../include/GameRectangle.h"
#include "Player.h"

void Game::start() {
  init();
  run();
  close();
}

void Game::init() {
  //  These should be in if statements (possibly nested)
  SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("Boxes", SDL_WINDOWPOS_UNDEFINED,
  SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  surface = SDL_GetWindowSurface(window);
  bg_surface = SDL_LoadBMP("assets/map/map.bmp");
}

void Game::draw() {
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 125, 125, 125));

  SDL_BlitSurface(bg_surface, NULL, surface, NULL);

  for (auto d : drawables) {
    d->draw(surface);
  }
  SDL_UpdateWindowSurface(window);
}

void Game::run() {
  Player *player = new Player();
  GameRectangle *r2 = new GameRectangle();

  player->setWidth(27);
  player->setHeight(30);

  player->loadSpriteFiles( { "assets/person/person-small-0.bmp",
      "assets/person/person-small-1.bmp", "assets/person/person-small-2.bmp" });

  r2->setX(100);
  r2->setY(100);

  r2->setWidth(81);
  r2->setHeight(46);
  r2->loadSpriteFiles( { "assets/block/block-small-0.bmp",
      "assets/block/block-small-1.bmp", });

  drawables.push_back(static_cast<IDrawable*>(player));
  drawables.push_back(static_cast<IDrawable*>(r2));

  physicals.push_back(static_cast<IOverlappable*>(player));
  physicals.push_back(static_cast<IOverlappable*>(r2));

  nonPhysicals.push_back(static_cast<IOverlappable*>(player));

  player->setPhysicalsList(&physicals);
  //r2->setPhysicalsList(&physicals);

  player->setNonPhysicalsList(&nonPhysicals);

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
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        player->travel(state);
      }
    }
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
