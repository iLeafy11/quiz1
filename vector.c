#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vector.h"

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


