#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void list_add_node_t(node_t **list, node_t *node_t) {
    node_t->next = *list;
    *list = node_t;
}

void list_concat(node_t **left, node_t *right) {
    while (*left)
        left = &(*left)->next;
    *left = right;
}

node_t *list_make_node_t(node_t *list, int entry) {
    node_t *new_node = malloc (sizeof(node_t));
    new_node->value = entry;
    new_node->next = list;
    return new_node;
}

void list_free(node_t **list) {
    node_t *temp = *list;
    while (*list) {
        temp = *list;
        *list = (*list)->next;
        free(temp);
    }
}

bool list_is_ordered(node_t *list) {
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

void list_display(node_t *list) {
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

