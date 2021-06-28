#include "food.h"

static food foods[FOODCOUNT] = {0};

void food_init() {
    for (int i=0; i<FOODCOUNT; i++) {
        foods[i] = (food) {
            (double) (rand() % (int) CELLS),
            (double) (rand() % (int) CELLS)
        };
        printf("foods[i] = {%f, %f}\n", foods[i].x, foods[i].y);
    }
}

void food_move(food* f) {
    f->x = (double) (rand() % (int) CELLS);
    f->y = (double) (rand() % (int) CELLS);
}

void map_food(void (*map)(food*)) {
    for (int i=0; i<FOODCOUNT; i++)
        map(&foods[i]);
}

void food_render(SDL_Renderer *rend, SDL_Texture *t_food) {
    for (int i=0; i<FOODCOUNT; i++) {
        SDL_RenderCopy(
            rend, t_food, NULL,
            &(SDL_Rect) {foods[i].x * CELLSIZE, foods[i].y * CELLSIZE, CELLSIZE, CELLSIZE});
    }
}
