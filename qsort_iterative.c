#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "list.h"
#include "vector.h"

/*
typedef struct __vnode {
    node_t *list;
    struct __vnode *next;
} vnode_t;

typedef struct __vector {
    vnode_t *top;
    bool (*isEmpty)(struct __vector *v);
    void (*push)(struct __vector *v, node_t *entry);
    node_t *(*pop)(struct __vector *v);
    void (*delete)(struct __vector *v);
} vector;

bool v_isEmpty(vector *v) 
{
    return (v->top == NULL);
}

void v_push(vector *v, node_t *entry) 
{
    if (!entry) return;
    vnode_t *new_vnode = malloc(sizeof(vnode_t));
    new_vnode->list = entry;
    new_vnode->next = v->top;
    v->top = new_vnode;
}

node_t *v_pop(vector *v) 
{
    if (v->isEmpty(v))
        return NULL;

    vnode_t *target = v->top;
    node_t *pop = target->list;
    v->top = target->next;
    free (target);
    target = NULL;
    return pop;
}

void v_delete(vector *v)
{
    if (v) {
        while (v->pop(v));
        free(v);
    }
}


vector *v_new() 
{
    vector *v = malloc(sizeof(vector));
    if (v) {
        v->top = NULL;
        v->isEmpty = v_isEmpty;
        v->push = v_push;
        v->pop = v_pop;
        v->delete = v_delete;
    }
    return v;
}
*/
void quicksort_iterative(node_t **list) 
{
    if (!*list || !(*list)->next) 
        return;

    vector *v = v_new();
    v->push(v, *list);
    node_t *result = NULL;
    while (v->top) {
        node_t *pivot = v->pop(v);
        if (pivot->next) {
            node_t *left = NULL, *right = NULL;
            int value = pivot->value;
            node_t *p = pivot->next;
            pivot->next = NULL;
            while (p) {
                node_t *n = p;
                p = p->next;
                list_add_node_t(n->value > value ? &right : &left, n);
            }
            v->push(v, left);
            v->push(v, pivot);
            v->push(v, right);
        } else 
            list_add_node_t(&result, pivot);        
    }
    *list = result;
    v->delete(v);
}

int main(int argc, char **argv) {
    srand(time(NULL));
    size_t count = 20;

    node_t *list = NULL;
    while (count--)
        list = list_make_node_t(list, random() % 1024);

    list_display(list);
    quicksort_iterative(&list);
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;

    list_free(&list);
    return EXIT_SUCCESS;
}

