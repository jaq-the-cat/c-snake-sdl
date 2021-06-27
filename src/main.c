#include "conf.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int CELLSIZE = SIDE/CELLSIDE; // cell size in pixels

SDL_Window *win;
SDL_Renderer *rend;

SDL_Texture *food;
SDL_Texture *snake_body;
SDL_Texture *snake_head;

void init() {
    // Window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        printf("Error initializing SDL: %s\n", SDL_GetError());
    win = SDL_CreateWindow(
        "SDL Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SIDE, SIDE,
        0);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    IMG_Init(IMG_INIT_PNG);

    food = IMG_LoadTexture(rend, "res/food.png");
    snake_body = IMG_LoadTexture(rend, "res/snake_body.png");
    snake_head = IMG_LoadTexture(rend, "res/snake_head.png");
}

int handleev() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_Q:
            return 1;
        if (event.key.type == SDL_KEYDOWN) {
            case SDL_SCANCODE_W:
                break;
            case SDL_SCANCODE_A:
                break;
            case SDL_SCANCODE_S:
                break;
            case SDL_SCANCODE_D:
                break;
        }
        default:
            break;
    }
    return 0;

}

void render() {
}

int main() {
    int close = 0;
    while (!close) {
        close = handleev();
        SDL_SetRenderDrawColor(rend, BACKGROUND, BACKGROUND, BACKGROUND, 255);
        SDL_RenderClear(rend);
        render();
        SDL_RenderPresent(rend);
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    return 0;
}
