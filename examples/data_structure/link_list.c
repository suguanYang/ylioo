#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"

typedef struct LNode {
    int data;
    struct LNode *next;
} *LinkList;

LinkList init_list() {
    LinkList L = (LinkList)malloc(sizeof(struct LNode));
    L->next = NULL;
    return L;
}

Status insert_list(LinkList L, int i, int e) {
    LinkList p = L;
    int j = 1;
    while (p->next && j < i) {
        p = p->next;
        j++;
    }
    if (j == i) {
        LinkList s = (LinkList)malloc(sizeof(struct LNode));
        s->data = e;
        s->next = p->next;
        p->next = s;
        return OK;
    }
    return ERROR;
}

Status delete_list(LinkList L, int i, int *e) {
    LinkList p = L;
    int j = 1;
    while (p->next && j < i) {
        p = p->next;
        j++;
    }
    if (j == i) {
        LinkList q = p->next;
        p->next = q->next;
        *e = q->data;
        free(q);
        return OK;
    }
    return ERROR;
}

int main() {
    long a = 2;
    int *b = NULL;
    int c = 1;
    float e = 0.1;

    b = (int*)malloc(sizeof(int));
    unsigned long addr = sizeof(a);
    addr = sizeof(b);
    addr = sizeof(c);

    return 1;
}
// 0x5555555592a0