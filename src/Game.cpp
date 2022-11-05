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
#include <sstream>

#include "../include/IDrawable.h"
#include "../include/IOverlappable.h"
#include "../include/GameRectangle.h"
#include "../include/VecRemover.h"
#include "../include/TextBox.h"
#include "../include/Person.h"
#include "../include/PersonSpawner.h"
#include "Obstacle.h"
#include "Player.h"
#include "Person.h"

void Game::start() {
  init();
  run();
  close();
}

void Game::updateScore(int s) {
  std::stringstream ss;
  ss << s;
  scoreTb.setText(ss.str());
}

void Game::init() {
    //  These should be in if statements (possibly nested)
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    window = SDL_CreateWindow("Boxes",SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
    gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
    bg_surface = SDL_LoadBMP("assets/map/map.bmp");

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
    AUDIO_CHANNELS, AUDIO_CHUNK_SIZE);
    mainTheme = Mix_LoadMUS("assets/sounds/Extra Life Jam theme.wav");
    destroyBlock = Mix_LoadWAV("assets/sounds/Destroy.wav");
    freedomSound = Mix_LoadWAV("assets/sounds/People End.wav");
    blockCreateSound = Mix_LoadWAV("assets/sounds/Barrier Spawn.wav");
    
    drawables.push_back(static_cast<IDrawable*>(&scoreTb));
    std::stringstream ss;
    ss << score;
    scoreTb.setText(ss.str());
    scoreTb.setWidth(SCORE_TB_WIDTH);
    scoreTb.setHeight(SCORE_TB_HEIGHT);
    scoreTb.setPosX(SCORE_TB_XLOC);
    scoreTb.setPosY(SCORE_TB_YLOC);
}

// TODO: For text - Move to header file
void Game::draw() {
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 125, 125, 125));

  SDL_BlitSurface(bg_surface, NULL, surface, NULL);

  for (auto d : drawables) {
    d->draw(surface);
  }
  SDL_UpdateWindowSurface (window);
}

void Game::run() {

    GameRectangle* endBox = new GameRectangle();
    int ebHeight = 5;
    endBox->setWidth(SCREEN_WIDTH);
    endBox->setHeight(ebHeight);
    endBox->setX(0);
    endBox->setY(SCREEN_HEIGHT - ebHeight);
    playerNonPhysicals.push_back(static_cast<IOverlappable*>(endBox));
    int score =0;
    endBox->addOverlapFunc([&score, this](GameRectangle* endBox)
    {
      this->updateScore(++score);
      Mix_PlayChannel(-1, this->freedomSound, 0);
    });

  Player *player1 = new Player(&physicals, &nonPhysicals);
  player1->playerNo = 1;

  player1->loadSpriteFiles({
    "assets/player/character-small-back-1.bmp",
    "assets/player/character-small-front-1.bmp",
    "assets/player/character-small-left-1.bmp",
    "assets/player/character-small-right-1.bmp"
    });
  drawables.push_back(static_cast<IDrawable*>(player1));

  
  Player *player2 = new Player(&physicals, &nonPhysicals);
  player2->playerNo = 2;
  player2->setX(50);

  player2->loadSpriteFiles({
    "assets/player/character-small-back-2.bmp",
    "assets/player/character-small-front-2.bmp",
    "assets/player/character-small-left-2.bmp",
    "assets/player/character-small-right-2.bmp"
    });
  drawables.push_back(static_cast<IDrawable*>(player2));

  //Obstacle* temp = new Obstacle(&physicals, &nonPhysicals);
  //temp->setX(90);
  //temp->setY(50);
  //drawables.push_back(temp);

  // TODO: Reanable

  ObstacleSpawner spawner(&physicals, &nonPhysicals, &drawables, &rGen);
  PersonSpawner pSpawner(&physicals, &nonPhysicals, &playerNonPhysicals, &drawables, &rGen);

  Mix_PlayMusic(mainTheme, -1);
  
  unsigned int frameCount =0;
  int personCount =0;
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
        player1->travel(state);
        player2->travel(state);
      }
    }
    //Update NPCS
    for (auto psn : people) {
      psn->travel();
    }
   if (frameCount % 300 == 0) {
    auto ps = pSpawner.spawnPeople(5, 0, SCREEN_WIDTH);
    people.insert(people.end(), ps.begin(), ps.end());
    personCount += ps.size();
   }
    if (frameCount % 30 == 0) {
      Obstacle* o;
      if ((o = spawner.spawnObstacle(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT)) != NULL) {
        o->addFunc([this, o](GameRectangle*){
          o->removeAll();
          VecRemover::remove(drawables, static_cast<IDrawable*>(o));
          Mix_PlayChannel(-1, destroyBlock, 0);
        });
       Mix_PlayChannel(-1, blockCreateSound, 0);
      }
    }
    ++frameCount;
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
