#pragma once
#include "util.h"

typedef struct s_node {
    vec2 position;
    struct s_node *next;
} s_node;

typedef struct {
    s_node *head;
    s_node *tail;
} snake;

void move(snake *s, vec2 dir);
int is_dead(snake *s);
