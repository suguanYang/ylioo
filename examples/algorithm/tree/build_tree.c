#include <stdlib.h>
#include <stdio.h>
// Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.
// Constraints:
// 1 <= preorder.length <= 3000
// inorder.length == preorder.length
// -3000 <= preorder[i], inorder[i] <= 3000
// preorder and inorder consist of unique values.
// Each value of inorder also appears in preorder.
// preorder is guaranteed to be the preorder traversal of the tree.
// inorder is guaranteed to be the inorder traversal of the tree.
struct ITreeNode {
     int val;
     struct ITreeNode *left;
     struct ITreeNode *right;
};

typedef struct ITreeNode TreeNode;


int MAX_SIZE = 6000;
int OFFSET = 3000;

int* buildInorderMap(int* inorder, int inorderSize) {
    int* map = malloc(sizeof(int) * MAX_SIZE);
    if (!map) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    for (int i = 0; i < inorderSize; i++) {
        map[inorder[i] + OFFSET] = i;
    }

    return map;
}

int getInorderIdx(int* map, int val) {
    return *(map + val + OFFSET);
}

TreeNode* search(TreeNode* node, int val) {
    if (!node) {
        return NULL;
    }

    if (node->val == val) return node;
    
    TreeNode* leftSearch = search(node->left, val);

    if (leftSearch) return leftSearch;

    return search(node->right, val);
}

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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    TreeNode* root = createNode(*preorder);
    if (!root) return NULL;
    int* map = buildInorderMap(inorder, inorderSize);
    int i = 1;

    TreeNode* parent = root;

    while (i < preorderSize) {
        TreeNode* node = createNode(*(preorder + i));
        node->val = *(preorder + i);
        int pIdx = getInorderIdx(map, parent->val);
        int nIdx = getInorderIdx(map, node->val);
        int gap = nIdx - pIdx;
        if (gap < 0) {
            parent->left = node;
        } else if (gap > 0) {
            TreeNode* prev = search(root, *(inorder + --nIdx));
            while (!prev) {
                prev = search(root, *(inorder + --nIdx));
            }
            prev->right = node;
        }

        parent = node;
        i++;
    }

    return root;
}


// void main() {
//     int preprder[5] = {3,9,20,15,7};
//     int inorder[5]  = {9,3,15,20,7};

//     buildTree(preprder, 5, inorder, 5);
// }