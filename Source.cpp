#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

using namespace std;

struct GameManager
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture* texture;
};

GameManager game_manager;

int game_manager_start() {
    SDL_Init(SDL_INIT_EVERYTHING);
    game_manager.window = SDL_CreateWindow("GameTheGame0x0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 512, SDL_WINDOW_RESIZABLE);
    if (game_manager.window == NULL) {
        cout << "Failed to create the window! Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }
    game_manager.renderer = SDL_CreateRenderer(game_manager.window, -1, 0);
    if (game_manager.renderer == NULL) {
        cout << "Failed to create the renderer! Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(game_manager.window);
        SDL_Quit();
        return 1;
    }
    game_manager.texture = SDL_CreateTexture(game_manager.renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, 512, 256);
    if (game_manager.texture == NULL) {
        cout << "Failed to create the texture! Error: " << SDL_GetError() << endl;
        SDL_DestroyRenderer(game_manager.renderer);
        SDL_DestroyWindow(game_manager.window);
        SDL_Quit();
        return 1;
    }
    SDL_Event event;
    bool must_loop = true;

    while (must_loop) {
        while (SDL_PollEvent(&event)) {
            // check event type
            switch (event.type) {
            case SDL_QUIT:
                // shut down
                must_loop = false;
                break;
            }
        }
        SDL_RenderClear(game_manager.renderer);
        SDL_RenderCopy(game_manager.renderer, game_manager.texture, NULL, NULL);
        SDL_RenderPresent(game_manager.renderer);
        SDL_Delay(16);
    }
    SDL_DestroyTexture(game_manager.texture);
    SDL_DestroyRenderer(game_manager.renderer);
    SDL_DestroyWindow(game_manager.window);
    SDL_Quit();
    return 0;
}

int main(int argc, char* args[]) {
    SDL_SetMainReady();
    return game_manager_start();
}