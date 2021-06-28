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
int enbiggen = 0;
const int MOV_DELAY = 10;

vec2 dir = {1, 0}; // wanted movement
vec2 mov = {1, 0}; // actual movement

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
    snek = s_init((vec2) {6, 6});
}

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
                    dir = (vec2) {0, -1};
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                if (mov.x == 0) // moving vertically
                    dir = (vec2) {-1, 0};
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                if (mov.y == 0) // moving horizontally
                    dir = (vec2) {0, 1};
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                if (mov.x == 0) // moving vertically
                    dir = (vec2) {1, 0};
                break;
        }
        default:
            break;
    }
    return 0;

}

void for_each_food(food* f) {
    if (f->x == snek.head->position.x
    && f->y == snek.head->position.y) {
        food_move(f);
        enbiggen = 1;
    }
}

void update() {
    mov = dir;
    s_move(&snek, mov, enbiggen);
    enbiggen = 0;
    map_food(for_each_food);
}

void render() {
    food_render(rend, t_food);
    s_render(rend, t_snake_body, &snek);
}

int main() {
    init();
    int tick = 0;
    while (1) {
        if (handleev()) break;
        SDL_SetRenderDrawColor(rend, BACKGROUND, BACKGROUND, BACKGROUND, 255);
        SDL_RenderClear(rend);
        if (tick >= MOV_DELAY) {
            tick = 0;
            update();
            if (s_is_dead(&snek)) break;
        } else
            tick++;
        render();
        SDL_RenderPresent(rend);
    }

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    return 0;
}
