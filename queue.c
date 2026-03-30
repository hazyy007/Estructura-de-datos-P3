#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "types.h"

struct _Queue {
    void *data[MAX_QUEUE];
    void **front;
    void **rear;
};

Queue *queue_new() {
    int i;
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (!q) return NULL;

    q->front = &(q->data[0]);
    q->rear = &(q->data[0]);

    for (i = 0; i < MAX_QUEUE; i++) {
        q->data[i] = NULL;
    }

    return q;
}

void queue_free(Queue *q) {
    if (q) free(q);
}

Bool queue_isEmpty(const Queue *q) {
    if (!q || q->front == q->rear) return TRUE;
    return FALSE;
}

Bool queue_isFull(const Queue *q) {
    if (!q) return TRUE;
    return (q->rear == &(q->data[MAX_QUEUE]));
}

Status queue_push(Queue *q, void *ele) {
    if (!q || !ele || queue_isFull(q)) return ERROR;

    *(q->rear) = ele;
    q->rear++;
    return OK;
}

void *queue_pop(Queue *q) {
    void *ele;
    if (!q || queue_isEmpty(q)) return NULL;

    ele = *(q->front);
    *(q->front) = NULL;
    q->front++;
    return ele;
}

void *queue_getFront(const Queue *q) {
    if (!q || queue_isEmpty(q)) return NULL;
    return *(q->front);
}

void *queue_getBack(const Queue *q) {
    if (!q || queue_isEmpty(q)) return NULL;
    return *(q->rear - 1);
}

size_t queue_size(const Queue *q) {
    if (!q) return 0;
    return (size_t)(q->rear - q->front);
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f) {
    int count = 0;
    void **ptr;
    if (!fp || !q || !f) return -1;

    for (ptr = q->front; ptr < q->rear; ptr++) {
        int res = f(fp, *ptr);
        if (res < 0) return -1;
        count += res;
        fprintf(fp, "\n");
    }
    return count;
}




