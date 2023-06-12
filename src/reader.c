#include <getter.h>
#include <reader.h>
#include <sort.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void compress(const char* inputFilename, const char* outputFilename)
{
    FILE* inputFile = fopen(inputFilename, "rb");
    FILE* outputFile = fopen(outputFilename, "wb");
    if (inputFile == NULL || outputFile == NULL)
        printf("Не удалось открыть файл %s",
               inputFile == NULL ? inputFilename : outputFilename);

    int freq[256] = {0};

    int length = getTextLength(inputFilename);
    uint8_t ch;
    while (fread(&ch, sizeof(uint8_t), 1, inputFile) == 1) {
        freq[ch]++;
    }

    struct Node* nodes[256];
    int n = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            nodes[n] = createNode(i, freq[i]);
            n++;
        } else {
            nodes[i] = NULL;
        }
    }

    quickSort(nodes, 0, n - 1);

    struct Node* root = buildTree(nodes, 0, n - 1);

    uint32_t codes[256] = {0};
    assignCodes(root, 0, codes);
    set_levels(root, 0);

    fwrite(&length, sizeof(int), 1, outputFile);
    fwrite(&n, sizeof(int), 1, outputFile);

    for (int i = 0; i < n; i++) {
        fwrite(&(nodes[i]->symbol), sizeof(uint8_t), 1, outputFile);
        fwrite(&(nodes[i]->freq), sizeof(int), 1, outputFile);
    }

    fseek(inputFile, 0, SEEK_SET);
    uint8_t buffer = 0;
    int bitsWritten = 0;
    while (fread(&ch, sizeof(uint8_t), 1, inputFile) == 1) {
        uint32_t code = codes[ch];
        int codeLength = findLevel(root, ch, 0);

        for (int i = 0; i < codeLength; i++) {
            if (code & (1 << (codeLength - i - 1))) {
                buffer |= (1 << (7 - bitsWritten));
            }

            bitsWritten++;

            if (bitsWritten == 8) {
                fwrite(&buffer, sizeof(uint8_t), 1, outputFile);
                buffer = 0;
                bitsWritten = 0;
            }
        }
    }

    if (bitsWritten > 0) {
        fwrite(&buffer, sizeof(uint8_t), 1, outputFile);
    }

    free_tree(root);

    fclose(inputFile);
    fclose(outputFile);
}
