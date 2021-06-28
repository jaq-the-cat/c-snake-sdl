#include "snake.h"

s_node* make_node(vec2 pos) {
    s_node *n = malloc(sizeof(s_node));
    n->position = pos;
    n->next = NULL;
    return n;
}

snake s_init(vec2 pos) {
    snake s = (snake) {
        NULL,
        NULL,
    };
    s.head = make_node(pos);
    s_node *n = s.head;
    for (int i=0; i<INITIALLEN; i++) {
        n->next = make_node((vec2) {pos.x-i, pos.y});
        n = n->next;
    }

    return s;
}

void s_move(snake *s, vec2 mov, int add) {
    vec2 prev = s->head->position;
    s->head->position.x += mov.x;
    s->head->position.y += mov.y;

    s_node *n;
    for (n = s->head->next; n != NULL; n = n->next) {
        printf("Current position: {%f, %f}\n", n->position.x, n->position.y);
        vec2 last = n->position;
        n->position = prev;
        prev = last;
    }
    if (add) {
        n->next = malloc(sizeof(s_node));
        n->next->position = n->position;
        n->next->next = NULL;
        s->tail = n->next;
    }
}

void s_render(SDL_Renderer *rend, SDL_Texture *t_snake, snake *s) {
    for (s_node *n = s->head; n != NULL; n = n->next) {
        SDL_RenderCopy(
            rend, t_snake, NULL,
            &(SDL_Rect) {n->position.x * CELLSIZE, n->position.y * CELLSIZE, CELLSIZE, CELLSIZE});
    }
}

int s_is_dead(snake *s) {
    for (s_node *n = s->head->next; n != NULL; n = n->next)
        if (s->head->position.x == n->position.x
        && s->head->position.y == n->position.y)
            return 1;
    return 0;
}
