// Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

// Example 1:
// Input: root = [3,9,20,null,null,15,7]
// Output: [[3],[20,9],[15,7]]
// Example 2:

// Input: root = [1]
// Output: [[1]]
#include <stdlib.h>
#include "build_tree.c"
#include <string.h>
typedef struct IArr
{
    int size;
    struct IArr **c_data;
    int *data;
    int cap;
} Arr;

Arr *construct(int cap, int type)
{
    Arr *arr = malloc(sizeof(Arr));
    if (cap == 0)
    {
        arr->cap = 2000;
    }
    else
    {
        arr->cap = cap;
    }
    if (type == 1)
    {
        arr->c_data = malloc(sizeof(Arr *) * arr->cap);
    }
    else
    {
        arr->data = malloc(sizeof(int) * arr->cap);
    }
    arr->size = 0;
    return arr;
}

void set_c(Arr *arr, int pos, Arr *s_arr)
{
    arr->c_data[pos] = s_arr;
}

void push_c(Arr *arr, Arr *s_arr)
{
    arr->c_data[arr->size] = s_arr;
    arr->size += 1;
}

void shift(Arr *arr, int val)
{
    arr->size += 1;
    for (int i = arr->size; i > 0; i--)
    {
        arr->data[i] = arr->data[i - 1];
    }
    arr->data[0] = val;
}

void push(Arr *arr, int val)
{
    arr->data[arr->size] = val;
    arr->size += 1;
}

int power(int base, int exponent) {
    int result = 1;
    if (exponent > 10) {
        return 2000;
    }
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

void inOrder(TreeNode *root, int depth, short direction, Arr *arr)
{
    if (!root)
        return;
    // print c_data address
    // exsure c_data and data are allocated
    if (depth >= arr->size)
    {
        push_c(arr, construct(power(2, depth + 1), 0));
    }
    inOrder(root->left, depth + 1, -direction, arr);
    if (direction == 1)
    {
        push(arr->c_data[depth], root->val);
    }
    else
    {
        shift(arr->c_data[depth], root->val);
    }
    inOrder(root->right, depth + 1, -direction, arr);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **zigzagLevelOrder(TreeNode *root, int *returnSize, int **returnColumnSizes)
{
    returnColumnSizes = malloc(sizeof(int *));
    returnSize = malloc(sizeof(int));
    Arr *cons = construct(0, 1);

    inOrder(root, 0, 1, cons);

    *returnColumnSizes = malloc(sizeof(int *) * cons->size);
    int **ret = malloc(sizeof(int *) * cons->size);

    *returnSize = cons->size;

    for (int i = 0; i < cons->size; i++)
    {
        int colSize = cons->c_data[i]->size;
        ret[i] = malloc(sizeof(int) * colSize);
        ret[i] = cons->c_data[i]->data;
        (*returnColumnSizes)[i] = colSize;
    }

    // print ret
    for (int i = 0; i < cons->size; i++)
    {
        for (int j = 0; j < (*returnColumnSizes)[i]; j++)
        {
            printf("%d ", ret[i][j]);
        }
        printf("\n");
    }

    return ret;
}

void main()
{
    int *returnSize;
    int **returnColumnSizes;
    // int preprder[5] = {1,2,4,3,5};
    // int inorder[5]  = {4,2,1,3,5};
    int preprder[5] = {3,9,20,15,7};
    int inorder[5]  = {9,3,15,20,7};
    TreeNode* root = buildTree(preprder, 5, inorder, 5);
    zigzagLevelOrder(root, returnSize, returnColumnSizes);
}