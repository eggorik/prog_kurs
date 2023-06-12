#include <tree.h>

#include <stdlib.h>

void set_levels(struct Node* root, int level)
{
    if (root == NULL) {
        return;
    } else {
        root->level = level;
        set_levels(root->left, level + 1);
        set_levels(root->right, level + 1);
    }
}

int findLevel(struct Node* root, int key, int level)
{
    if (root == NULL) {
        return -1;
    }
    if (root->symbol == key) {
        return level;
    }
    int leftLevel = findLevel(root->left, key, level + 1);
    if (leftLevel != -1) {
        return leftLevel;
    }
    return findLevel(root->right, key, level + 1);
}

struct Node* createNode(uint8_t symbol, int frequency)
{
    struct Node* node = NULL;
    node = (struct Node*)malloc(sizeof(struct Node));
    node->symbol = symbol;
    node->freq = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct Node* buildTree(struct Node** nodes, int start, int end)
{
    if (start > end) {
        return NULL;
    }

    if (start == end) {
        return nodes[start];
    }

    int sum = 0;
    for (int i = start; i <= end; i++) {
        if (nodes[i] != NULL) {
            sum += nodes[i]->freq;
        }
    }

    int currSum = 0;
    int i = start;
    struct Node* node;

    while (currSum < sum / 2) {
        if (nodes[i] != NULL) {
            currSum += nodes[i]->freq;
        }
        i++;
    }

    node = createNode(0, currSum);
    node->left = buildTree(nodes, start, i - 1);
    node->right = buildTree(nodes, i, end);

    return node;
}

void free_tree(struct Node* tree)
{
    if (tree->left)
        free_tree(tree->left);
    if (tree->right)
        free_tree(tree->right);
    free(tree);
}