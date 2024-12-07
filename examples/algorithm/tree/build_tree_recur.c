#include <stdlib.h>
#include <stdio.h>

struct ITreeNode {
     int val;
     struct ITreeNode *left;
     struct ITreeNode *right;
};

typedef struct ITreeNode TreeNode;

TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int pop(int** arr, int* len) {
    int first = *(*arr);
    if (*len > 1) {
        *arr = *arr + 1;
    }
    (*len)--;
    return first;
}

int findIdx(int* arr, int len, int val) {
    int i = 0;
    while (i < len) {
        if (*(arr + i) == val) {
            return i;
        }
        i++;
    }

    return -1;
}

void split(int* arr, int len, int p, int** left, int** right) {
    if (p > 0) {
        *left = (int*)malloc(sizeof(int) * p);
        for (int i = 0; i < p; i++) {
            (*left)[i] = *(arr + i);
        }
    }
    if (p < len - 1) {
        *right = (int*)malloc(sizeof(int) * (len - p - 1));
        for (int i = p + 1; i < len; i++) {
            (*right)[i - p - 1] = *(arr + i);
        }
    }

}

TreeNode* iter(int** preorder, int* preorderSize, int* inorder, int inorderSize) {
    if (inorderSize == 0) {
        return NULL;
    };
    int val = pop(preorder, preorderSize);
    int valIdx = findIdx(inorder, inorderSize, val);

    TreeNode* root = createNode(val);

    int* leftTree; int* rightTree;
    split(inorder, inorderSize, valIdx, &leftTree, &rightTree);
    int rLen = inorderSize - valIdx - 1;
    root->left = iter(preorder, preorderSize, leftTree, valIdx);
    root->right = iter(preorder, preorderSize, rightTree, rLen);

    return root;
}

/**
 * Base Step: the first node A of preorder array is the root node; In the inorder array, the nodes brefore A
 * is the left subtree of the A, the node after the A, is the right subtree of the A
 * Induction Step: A = preorder.first(), A.leftTree = inorder[0: A-1], A.rightTree = inorder[A+1:len]
 * By the defintion of preorder traverse, the next node of preorder array will be the root node of A.leftTree
 * thus B = preorder.next(), B.leftTree = inorder[0: A-1][0:B-1], B.rightTree = inorder[0: A-1][B+1:A-1]
 */
TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    return iter(&preorder, &preorderSize, inorder, inorderSize);
}

int main() {
    int preorder[4] = {3,9,20,15};
    int inorder[4]  = {9,3,15,20};

    buildTree(preorder, 4, inorder, 4);
}