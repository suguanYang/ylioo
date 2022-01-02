#include <stdlib.h>
#include <stdio.h>
#include "types.h"

struct Term {
    int coef;
    int expn;
    struct Term *next;
};

struct LinkList {
    struct Term *head;
    int len;
};

typedef struct LinkList *Polynomial;

Status create_polynomial(Polynomial L) {
    L = (Polynomial)malloc(sizeof(struct LinkList));
    L->head = NULL;
    return OK;
}

void destory_polynomial(Polynomial L) {
    struct Term *p = L->head;
    while (p) {
        struct Term *q = p->next;
        free(p);
        p = q;
    }
    free(L);
}

void print_polynomial(Polynomial L) {
    struct Term *p = L->head;
    while (p) {
        printf("%dX^%d", p->coef, p->expn);
        p = p->next;
    }
    printf("\n");
}

int poly_len(Polynomial L) {
    return L->len;
}

int cmp_term_expn(struct Term *t1, struct Term *t2) {
    if (t1->expn == t2->expn) {
        return 0;
    } else if (t1->expn > t2->expn) {
        return 1;
    } else {
        return -1;
    }
}

void add_polynomial(Polynomial L1, Polynomial L2, Polynomial out) {
    struct Term *p1 = L1->head;
    struct Term *p2 = L2->head;
    struct Term *p3 = out->head;
    while (p1 && p2) {
        if (cmp_term_expn(p1, p2) == 0) {
            p3->coef = p1->coef + p2->coef;
            p3->expn = p1->expn;
            p1 = p1->next;
            p2 = p2->next;
        } else if (cmp_term_expn(p1, p2) == 1) {
            p3->coef = p1->coef;
            p3->expn = p1->expn;
            p1 = p1->next;
        } else {
            p3->coef = p2->coef;
            p3->expn = p2->expn;
            p2 = p2->next;
        }
        p3->next = (struct Term *)malloc(sizeof(struct Term));
        p3 = p3->next;
    }
    while (p1) {
        p3->coef = p1->coef;
        p3->expn = p1->expn;
        p1 = p1->next;
        p3->next = (struct Term *)malloc(sizeof(struct Term));
        p3 = p3->next;
    }
    while (p2) {
        p3->coef = p2->coef;
        p3->expn = p2->expn;
        p2 = p2->next;
        p3->next = (struct Term *)malloc(sizeof(struct Term));
        p3 = p3->next;
    }
    p3->next = NULL;
    // out->len = L1->len + L2->len;
}

void mutiply_polynomial(Polynomial L1, Polynomial L2, Polynomial out) {
    struct Term *p1 = L1->head;
    struct Term *p2 = L2->head;
    struct Term *p3 = out->head;
    while (p1) {
        while (p2) {
            p3->coef = p1->coef * p2->coef;
            p3->expn = p1->expn + p2->expn;
            p3->next = (struct Term *)malloc(sizeof(struct Term));
            p3 = p3->next;
            p2 = p2->next;
        }
        p2 = L2->head;
        p1 = p1->next;
    }
    p3->next = NULL;
    // out->len = L1->len + L2->len;
}
