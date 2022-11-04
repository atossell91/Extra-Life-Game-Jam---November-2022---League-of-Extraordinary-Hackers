#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <string>

#include "IDrawable.h"
#include "IOverlappable.h"

class Game {
 private:
    SDL_Window* window = NULL;
    SDL_Surface* surface = NULL;
    SDL_Surface* bg_surface = NULL;
    Mix_Music* mainTheme;
    Mix_Chunk* destroyBlock;

    std::vector<IDrawable*> drawables;
    std::vector<IOverlappable*> physicals;
    std::vector<IOverlappable*> nonPhysicals;
    std::vector<IOverlappable*> playerNonPhysicals;

    enum EnumLayers {Bottom, Middle, Top};
    const EnumLayers TopLayer = EnumLayers::Top;

    const int NUM_LAYERS = TopLayer + 1;
    const int MAX_NUM = 2147483647;
    const int INTERVAL = MAX_NUM / NUM_LAYERS;
    
    void init();
    void draw();
    void run();
    void close();

public:
    const int SCREEN_HEIGHT = 640;
    const int SCREEN_WIDTH = 960;

    const int AUDIO_CHANNELS = 2;
    const int AUDIO_CHUNK_SIZE = 2048;

    void start();
};

#endif  // INCLUDE_GAME_H_
