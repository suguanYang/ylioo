#include "../types.h"

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

typedef struct {
    int size;
    int *top;
    int *base;
} Stack;

Status init_stack(Stack S);

Status destroy_stack(Stack S);

Status pop_stack(Stack S, int *e);

Status push_stack(Stack S, int e);
