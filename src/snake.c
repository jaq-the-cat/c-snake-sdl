#include "snake.h"
#include <stdlib.h>

void move(snake *s, vec2 mov) {
    s->head->position.x += mov.x;
    s->head->position.y += mov.y;
    for (s_node *n = s->head; n->next != NULL; n = n->next)
        n->next->position = n->position;
}

int is_dead(snake *s) {
    for (s_node *n = s->head->next; n != NULL; n = n->next)
        if (s->head->position.x == n->position.x
        && s->head->position.y == n->position.y)
            return 1;
    return 0;
}
