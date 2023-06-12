#include <getter.h>
#include <stdio.h>

void assignCodes(struct Node* node, uint32_t code, uint32_t* codes)
{
    if (node->left) {
        assignCodes(node->left, code << 1, codes);
    }

    if (node->right) {
        assignCodes(node->right, (code << 1) | 0x01, codes);
    }

    if (!node->left && !node->right)
        codes[node->symbol] = code;
}

int getTextLength(const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return -1;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return -1;
    }

    long length = ftell(file);
    if (length == -1) {
        fclose(file);
        return -1;
    }

    fclose(file);

    return length;
}