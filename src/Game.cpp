#include "../include/Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

#include "../include/IDrawable.h"
#include "../include/IOverlappable.h"
#include "../include/GameRectangle.h"
#include "Player.h"
#include "Person.h"
void Game::start() {
  init();
  run();
  close();
}

void Game::init() {
  //  These should be in if statements (possibly nested)
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  window = SDL_CreateWindow("Boxes", SDL_WINDOWPOS_UNDEFINED,
  SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  surface = SDL_GetWindowSurface(window);
  bg_surface = SDL_LoadBMP("assets/map/map.bmp");

  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, AUDIO_CHANNELS,
                AUDIO_CHUNK_SIZE);
  mainTheme = Mix_LoadMUS("assets/sounds/Extra Life Jam theme.wav");
}

void Game::draw() {
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 125, 125, 125));

  SDL_BlitSurface(bg_surface, NULL, surface, NULL);

  for (auto d : drawables) {
    d->draw(surface);
  }
  SDL_UpdateWindowSurface (window);
}

void Game::run() {
  Player *player = new Player();
  GameRectangle *r2 = new GameRectangle();
  Person *people[10];
  int tempH = 100;
  int tempW = 100;
  for (int i = 0; i < 10; i++) {
    people[i] = new Person;
    people[i]->setX(tempW);
    people[i]->setY(tempH);
    people[i]->setWidth(27);
    people[i]->setHeight(30);
    tempW += 50;
    people[i]->loadSpriteFiles(
        { "assets/person/person-small-0.bmp",
            "assets/person/person-small-1.bmp",
            "assets/person/person-small-2.bmp" });
    drawables.push_back(static_cast<IDrawable*>(people[i]));
    physicals.push_back(static_cast<IOverlappable*>(people[i]));
  }
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

  for (int i = 0; i < 10; i++) {
    people[i]->setPhysicalsList(&physicals);
    people[i]->setNonPhysicalsList(&nonPhysicals);
  }

  Mix_PlayMusic(mainTheme, -1);

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
    //Update NPCS
    for (int i = 0; i < 10; i++) {
      people[i]->travel();
    }
    draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(17));
  }
  Mix_HaltMusic();
}

void Game::close() {
  SDL_FreeSurface (bg_surface);
  bg_surface = NULL;
  SDL_DestroyWindow (window);
  SDL_Quit();
}
