#pragma once
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "util.h"
#include "conf.h"

typedef vec2 food;

void food_init();
void food_move(food* f);
void food_render(SDL_Renderer *rend, SDL_Texture *t_food);
void map_food(void (*map)(food*));
