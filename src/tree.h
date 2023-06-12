#pragma once

#include <stdint.h>

struct Node {
    uint8_t symbol;
    int freq;
    int level;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(uint8_t symbol, int frequency);
void set_levels(struct Node* root, int level);
void free_tree(struct Node* tree);

struct Node* buildTree(struct Node** nodes, int start, int end);
int findLevel(struct Node* root, int key, int level);
