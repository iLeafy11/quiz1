#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

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

static inline void list_add_node_t(node_t **list, node_t *node_t) {
    node_t->next = *list;
    *list = node_t;
}

static inline void list_concat(node_t **left, node_t *right) {
    while (*left)
        left = &(*left)->next;
    *left = right;
}

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

void quicksort(node_t **list)
{
    if (!*list)
        return;

    node_t *pivot = *list;
    int value = pivot->value;
    node_t *p = pivot->next;
    pivot->next = NULL;

    node_t *left = NULL, *right = NULL;
    while (p) {
        node_t *n = p;
        p = p->next;
        list_add_node_t(n->value > value ? &right : &left, n);
    }

    quicksort(&left);
    quicksort(&right);

    node_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot);
    list_concat(&result, right);
    *list = result;
}

static node_t *list_make_node_t(node_t *list, int entry) {
    node_t *new_node = malloc (sizeof(node_t));
    new_node->value = entry;
    new_node->next = list;
    return new_node;
}

static void list_free(node_t **list) {
    node_t *temp = *list;
    while (*list) {
        temp = *list;
        *list = (*list)->next;
        free(temp);
    }
}

static bool list_is_ordered(node_t *list) {
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

static void list_display(node_t *list) {
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
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

