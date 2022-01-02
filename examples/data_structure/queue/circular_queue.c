// A circular queue using a contiguous block of memory to store data
// circular means when the tail pointer reaches the end of the memory
// it will start from the beginning of the memory.
#include "../types.h"
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef struct {
    int *base;
    int tail;
    int head;
} CircularQueue;

Status init_queue(CircularQueue Q) {
    Q.base = (int*)malloc(sizeof(int) * MAX_QUEUE_SIZE);
    if (Q.base == NULL) {
        return ERROR;
    }
    Q.tail = 0;
    Q.head = 0;
    return OK;
}

int queue_len(CircularQueue Q) {
    return (Q.tail + MAX_QUEUE_SIZE - Q.head) % MAX_QUEUE_SIZE;
}

Status en_queue(CircularQueue Q, int e) {
    if (queue_len(Q) == MAX_QUEUE_SIZE - 1) {
        return ERROR;
    }

    Q.base[Q.tail] = e;
    Q.tail = (Q.tail + 1) % MAX_QUEUE_SIZE;
    return OK;
}


