#include "../include/Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>

#include "../include/IDrawable.h"
#include "../include/IOverlappable.h"
#include "../include/GameRectangle.h"
#include "../include/VecRemover.h"
#include "Obstacle.h"
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
    TTF_Init();
    window = SDL_CreateWindow("Boxes",SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
    bg_surface = SDL_LoadBMP("assets/map/map.bmp");

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
    AUDIO_CHANNELS, AUDIO_CHUNK_SIZE);
    mainTheme = Mix_LoadMUS("assets/sounds/Extra Life Jam theme.wav");
    destroyBlock = Mix_LoadWAV("assets/sounds/Destroy.wav");
    freedomSound = Mix_LoadWAV("assets/sounds/People End.wav");
}

// TODO: For text - Move to header file
SDL_Rect tr;
SDL_Surface* tSurf;
void Game::draw() {
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 125, 125, 125));

  SDL_BlitSurface(bg_surface, NULL, surface, NULL);

  for (auto d : drawables) {
    d->draw(surface);
  }
  SDL_BlitSurface(tSurf, NULL, surface, NULL);
  SDL_UpdateWindowSurface (window);
}

void Game::run() {
    // Text stuff (practice)
    tr.w = 200;
    tr.h = 80;
    tr.x = SCREEN_WIDTH - tr.w;
    tr.y = 0;
    TTF_Font* font = TTF_OpenFont("assets/Connection II-1260.ttf", 48);
    SDL_Color Black = {0, 0, 0};
    tSurf = TTF_RenderText_Solid(font, "Hello", Black);
    // Text stuff ends above here

    GameRectangle* endBox = new GameRectangle();
    int ebHeight = 5;
    endBox->setWidth(SCREEN_WIDTH);
    endBox->setHeight(ebHeight);
    endBox->setX(0);
    endBox->setY(SCREEN_HEIGHT - ebHeight);
    nonPhysicals.push_back(static_cast<IOverlappable*>(endBox));
    int score =0;
    endBox->addOverlapFunc([&score, this](GameRectangle* endBox)
    {
      ++score; std::cout << "Score is: " << score << std::endl;
      Mix_PlayChannel(-1, this->freedomSound, 0);
    });
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
    nonPhysicals.push_back(static_cast<IOverlappable*>(people[i]));
  }
  player->setWidth(27);
  player->setHeight(30);

  player->loadSpriteFiles( { "assets/person/person-small-0.bmp",
      "assets/person/person-small-1.bmp", "assets/person/person-small-2.bmp" });

  drawables.push_back(static_cast<IDrawable*>(player));

  physicals.push_back(static_cast<IOverlappable*>(player));

  playerNonPhysicals.push_back(static_cast<IOverlappable*>(player));

  player->setPhysicalsList(&physicals);
  player->setNonPhysicalsList(&playerNonPhysicals);

  Obstacle* o = new Obstacle(&physicals, &playerNonPhysicals);
  o->setX(200);
  o->setY(200);
  o->addFunc([&o, this](GameRectangle* gr){
    o->removeAll();
    VecRemover::remove(drawables, static_cast<IDrawable*>(o));
    Mix_PlayChannel(-1, destroyBlock, 0);
  });
  drawables.push_back(static_cast<IDrawable*>(o));

  //player->setNonPhysicalsList(&nonPhysicals);

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
