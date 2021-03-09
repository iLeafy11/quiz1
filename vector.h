#ifndef VECTOR_H
#define VECTOR_H

#include "list.h"

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

bool v_isEmpty(vector *v);

void v_push(vector *v, node_t *entry);

node_t *v_pop(vector *v);

void v_delete(vector *v);

vector *v_new();

#endif
