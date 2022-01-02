#include "stack.h"
#include <stdlib.h>

Status init_stack(Stack S) {
    S.base = (int*)malloc(sizeof(int) * STACK_INIT_SIZE);
    S.top = S.base;
    S.size = STACK_INIT_SIZE;
    return OK;
}

Status destroy_stack(Stack S) {
    free(S.base);
    S.base = NULL;
    S.top = NULL;
    S.size = 0;
    return OK;
}

Status pop_stack(Stack S, int *e) {
    if (S.top == S.base) {
        return ERROR;
    }
    *e = *(--S.top);
    return OK;
}

Status push_stack(Stack S, int e) {
    if (S.top - S.base >= S.size) {
        S.base = (int*)realloc(S.base, sizeof(int) * (S.size + STACK_INCREMENT));
        S.top = S.base + S.size;
        S.size += STACK_INCREMENT;
    }
    *S.top++ = e;
    return OK;
}

