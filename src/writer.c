#include <tree.h>
#include <writer.h>

#include <stdint.h>
#include <stdio.h>

void decompress(const char* inputFilename, const char* outputFilename)
{
    FILE* inputFile = fopen(inputFilename, "rb");
    FILE* outputFile = fopen(outputFilename, "wb");

    int inputLength;
    int numSymbols;
    fread(&inputLength, sizeof(int), 1, inputFile);
    fread(&numSymbols, sizeof(int), 1, inputFile);

    struct Node* nodes[256];

    for (int i = 0; i < 256; i++) {
        nodes[i] = NULL;
    }

    for (int i = 0; i < numSymbols; i++) {
        uint8_t symbol;
        int freq;
        fread(&symbol, sizeof(uint8_t), 1, inputFile);
        fread(&freq, sizeof(int), 1, inputFile);
        nodes[i] = createNode(symbol, freq);
    }

    struct Node* root = buildTree(nodes, 0, numSymbols - 1);

    struct Node* current = root;
    uint8_t buffer;
    int bitIndex = 0;
    int outputLength = 0;
    while (outputLength < inputLength) {
        if (bitIndex == 0) {
            fread(&buffer, sizeof(uint8_t), 1, inputFile);
            bitIndex = 8;
        }
        if (buffer & 0x80) {
            current = current->right;
        } else {
            current = current->left;
        }
        buffer <<= 1;
        bitIndex--;
        if (current->left == NULL && current->right == NULL) {
            fwrite(&(current->symbol), sizeof(uint8_t), 1, outputFile);
            current = root;
            outputLength++;
        }
    }

    free_tree(root);

    fclose(inputFile);
    fclose(outputFile);
}