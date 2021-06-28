#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "conf.h"
#include "food.h"
#include "snake.h"

SDL_Window *win;
SDL_Renderer *rend;

SDL_Texture *t_food;
SDL_Texture *t_snake_body;
SDL_Texture *t_snake_head;

snake snek;

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

    // Textures
    IMG_Init(IMG_INIT_PNG);
    t_food = IMG_LoadTexture(rend, "res/food.png");
    t_snake_body = IMG_LoadTexture(rend, "res/snake_body.png");
    t_snake_head = IMG_LoadTexture(rend, "res/snake_head.png");

    // Things
    food_init();
    snek = s_init((vec2) {3, 3});
}

vec2 mov = {1, 0};

int handleev() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
        case SDL_SCANCODE_Q:
            return 1;
        if (event.key.type == SDL_KEYDOWN) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                if (mov.y == 0) // moving horizontally
                    mov = (vec2) {0, -1};
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                if (mov.x == 0) // moving vertically
                    mov = (vec2) {1, 0};
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                if (mov.y == 0) // moving horizontally
                    mov = (vec2) {0, 1};
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                if (mov.x == 0) // moving vertically
                    mov = (vec2) {-1, 0};
                break;
        }
        default:
            break;
    }
    return 0;

}

void update() {
    s_move(&snek, mov, 0);
}

void render() {
    food_render(rend, t_food);
    s_render(rend, t_snake_body, &snek);
}

int main() {
    init();
    int close = 0;
    while (!close) {
        close = handleev();
        SDL_SetRenderDrawColor(rend, BACKGROUND, BACKGROUND, BACKGROUND, 255);
        SDL_RenderClear(rend);

        update();
        render();

        SDL_RenderPresent(rend);
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    return 0;
}
