#pragma once
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "util.h"
#include "conf.h"

typedef struct s_node {
    vec2 position;
    struct s_node *next;
} s_node;

typedef struct {
    s_node *head;
    s_node *tail;
} snake;

snake s_init(vec2 pos);
void s_move(snake *s, vec2 dir, int add);
void s_render(SDL_Renderer *rend, SDL_Texture *t_snake, snake *s);
int s_is_dead(snake *s);
