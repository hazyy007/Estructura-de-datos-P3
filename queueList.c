#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "list.h"

struct _Queue {
    List *pl;
};

Queue *queue_new() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (!q) return NULL;
    
    q->pl = list_new();
    if (!q->pl) {
        free(q);
        return NULL;
    }
    return q;
}

void queue_free(Queue *q) {
    if (!q) return;
    list_free(q->pl);
    free(q);
}

Bool queue_isEmpty(const Queue *q) {
    if (!q) return TRUE;
    return list_isEmpty(q->pl);
}

Status queue_push(Queue *q, void *ele) {
    if (!q || !ele) return ERROR;
    /* En una cola se inserta por detrás (rear/back) */
    return list_pushBack(q->pl, ele);
}

void *queue_pop(Queue *q) {
    if (!q) return NULL;
    /* En una cola se extrae por delante (front) */
    return list_popFront(q->pl);
}

void *queue_getFront(const Queue *q) {
    if (!q) return NULL;
    return list_getFront(q->pl);
}

void *queue_getBack(const Queue *q) {
    if (!q) return NULL;
    return list_getBack(q->pl);
}

size_t queue_size(const Queue *q) {
    if (!q) return 0;
    return list_size(q->pl);
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f) {
    if (!fp || !q || !f) return -1;
    /* Transformamos el puntero a función para que coincida con el de la lista */
    return list_print(fp, q->pl, (p_list_ele_print)f);
}