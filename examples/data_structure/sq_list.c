#include <stdlib.h>
#include <stdio.h>
#include "types.h"

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct {
    int *elem;
    int length;
    int listSize;
} SqList;

SqList *init_list() {
    SqList* L = (SqList *)malloc(sizeof(SqList));
    L->elem = (int *)malloc(LIST_INIT_SIZE * sizeof(int));
    L->length = 0;
    L->listSize = LIST_INIT_SIZE;
    return L;
}

Status insert_list(SqList *L, int i, int e) {
    if (i < 1 || i > L->length + 1) {
        return ERROR;
    }
    if (L->length >= L->listSize) {
        L->listSize += LISTINCREMENT;
        L->elem = (int *)realloc(
            L->elem,
            L->listSize * sizeof(int)
        );
    }
    for (int j = L->length; j >= i; j--) {
        L->elem[j] = L->elem[j - 1];
    }
    L->elem[i - 1] = e;
    L->length++;
    return OK;
}

Status delete_list(SqList *L, int i, int *e) {
    if (i < 1 || i > L->length) {
        return ERROR;
    }
    *e = L->elem[i - 1];
    for (int j = i; j < L->length; j++) {
        L->elem[j - 1] = L->elem[j];
    }
    L->length--;
    return OK;
}

int is_greater(int a, int b) {
    return a > b;
}

void sort_array(int *arr, int len, int compare(int, int)) {
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (compare(arr[i], arr[j])) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

int main() {
    int *arr = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        *(arr + i) = rand() % 100;
        printf("%d ", *(arr + i));
    }
    printf("\n");
    sort_array(arr, 10, is_greater);
    for (int i = 0; i < 10; i++) {
        printf("%d ", *(arr + i));
    }

    return 0;
}