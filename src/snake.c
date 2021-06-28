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
    printf("Snake head: {%f, %f}\n", s.head->position.x, s.head->position.y);
    s_node *n = s.head;
    for (int i=1; i<INITIALLEN-1; i++) {
        n->next = make_node((vec2) {pos.x-i, pos.y});
        printf("Snake node: {%f, %f}\n", n->next->position.x, n->next->position.y);
    }

    return s;
}

void s_move(snake *s, vec2 mov, int add) {
    vec2 prev = s->head->position;
    s->head->position.x += mov.x;
    s->head->position.y += mov.y;

    s_node *n;
    for (n = s->head; n->next != NULL; n = n->next) {
        n->next->position = prev;
        prev = n->position;
    }
    if (add) {
        n->next = malloc(sizeof(s_node));
        n->next->position = n->position;
        n->next->next = NULL;
        s->tail = n->next;
    }
}

void s_render(SDL_Renderer *rend, SDL_Texture *t_snake, snake *s) {
    printf("RENDER: \n");
    for (s_node *n = s->head; n != NULL; n = n->next) {
        printf("Rendering {%f, %f}\n", n->position.x, n->position.y);
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
