#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "conf.h"
#include "food.h"

SDL_Window *win;
SDL_Renderer *rend;

SDL_Texture *t_food;
SDL_Texture *t_snake_body;
SDL_Texture *t_snake_head;

void init() {
    // Window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
    win = SDL_CreateWindow(
        "jaq-the-cat/c-snake-sdl",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SIDE, SIDE,
        0);
    rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    IMG_Init(IMG_INIT_PNG);

    t_food = IMG_LoadTexture(rend, "res/food.png");
    t_snake_body = IMG_LoadTexture(rend, "res/snake_body.png");
    t_snake_head = IMG_LoadTexture(rend, "res/snake_head.png");

    food_init();
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
    food_render(rend, t_food);
}

int main() {
    init();
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
