#include "../include/Game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <vector>
#include <iostream>
#include <Algorithm>
#include <thread>
#include <chrono>

#include "../include/IDrawable.h"
#include "../include/IOverlappable.h"
#include "../include/GameRectangle.h"

template <typename T>
void Game::eraseFromVector(std::vector<T>& vec, T elem) {
    auto i = vec.begin();
    for (; i != vec.end(); ++i) {
        if (*i == elem) {
            break;
        }
    }
    if (i != vec.end()) {
        vec.erase(i);
    }
}

void Game::start() {
    init();
    run();
    close();
}

void Game::init() {
    //  These should be in if statements (possibly nested)
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow("Boxes",SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
    bg_surface = SDL_LoadBMP("assets/map/map.bmp");

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
    AUDIO_CHANNELS, AUDIO_CHUNK_SIZE);
    mainTheme = Mix_LoadMUS("assets/sounds/Extra Life Jam theme.wav");
    destroyBlock = Mix_LoadWAV("assets/sounds/Destroy.wav");
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

    GameRectangle* playerObject = new GameRectangle();
    playerObject->setWidth(27);
    playerObject->setHeight(30);
    playerObject->loadSpriteFiles({
        "assets/person/person-small-0.bmp",
        "assets/person/person-small-1.bmp",
        "assets/person/person-small-2.bmp"
    });
    drawables.push_back(static_cast<IDrawable*>(playerObject));
    physicals.push_back(static_cast<IOverlappable*>(playerObject));
    nonPhysicals.push_back(static_cast<IOverlappable*>(playerObject));
    playerObject->setPhysicalsList(&physicals);
    //r2->setPhysicalsList(&physicals);
    playerObject->setNonPhysicalsList(&nonPhysicals);

    //  TODO: Handle the leaking memory
    GameRectangle* bottomBox = new GameRectangle();
    int bottomBoxHeight = 20;
    bottomBox->setWidth(SCREEN_WIDTH);
    bottomBox->setHeight(bottomBoxHeight);
    bottomBox->setX(0);
    bottomBox->setY(SCREEN_HEIGHT - bottomBoxHeight);
    //TODO: Change this
    //bottomBox->addOverlapFunc([this](GameRectangle* r){std::cout << "An overlap has occured" << std::endl;});
    //drawables.push_back(static_cast<IDrawable*>(r3)); // Comment out to hide
    nonPhysicals.push_back(static_cast<IOverlappable*>(bottomBox));

    GameRectangle* blockObject1 = new GameRectangle();
    blockObject1->setX(100);
    blockObject1->setY(100);
    blockObject1->setWidth(81);
    blockObject1->setHeight(46);
    blockObject1->loadSpriteFiles({
        "assets/block/block-small-0.bmp",
        "assets/block/block-small-1.bmp",
    });
    drawables.push_back(static_cast<IDrawable*>(blockObject1));
    physicals.push_back(static_cast<IOverlappable*>(blockObject1));

    GameRectangle* qa = new GameRectangle();
    int margin = 20;
    qa->setWidth(81 + margin*2);
    qa->setHeight(46 + margin*2);
    qa->setX(250 - margin);
    qa->setY(250 - margin);
    nonPhysicals.push_back(static_cast<IOverlappable*>(qa));
    drawables.push_back(static_cast<IDrawable*>(qa));
    GameRectangle* destroyableBlock = new GameRectangle();
    destroyableBlock->setWidth(81);
    destroyableBlock->setHeight(46);
    destroyableBlock->setX(250);
    destroyableBlock->setY(250);
    destroyableBlock->loadSpriteFiles({
        "assets/block/block-small-0.bmp",
        "assets/block/block-small-1.bmp",
    });
    qa->addOverlapFunc([this, qa, destroyableBlock](GameRectangle* r){
        eraseFromVector(drawables, static_cast<IDrawable*>(qa));
        eraseFromVector(nonPhysicals, static_cast<IOverlappable*>(qa));
        eraseFromVector(drawables, static_cast<IDrawable*>(destroyableBlock));
        eraseFromVector(physicals, static_cast<IOverlappable*>(destroyableBlock));
        Mix_PlayChannel(-1, destroyBlock, 0);
    });
    drawables.push_back(destroyableBlock);
    physicals.push_back(destroyableBlock);

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
                const Uint8* state = SDL_GetKeyboardState(NULL);
                if (state[SDL_SCANCODE_UP]) {
                    playerObject->moveY(-amt);
                }
                if (state[SDL_SCANCODE_DOWN]) {
                    playerObject->moveY(amt);
                }
                if (state[SDL_SCANCODE_LEFT]) {
                    playerObject->moveX(-amt);
                }
                if (state[SDL_SCANCODE_RIGHT]) {
                    playerObject->moveX(amt);
                }
            }
        }
        draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    }

    Mix_HaltMusic();
}

void Game::close() {
    SDL_FreeSurface(bg_surface);
    bg_surface = NULL;
    SDL_DestroyWindow(window);
    SDL_Quit();
}