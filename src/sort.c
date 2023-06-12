#include <sort.h>

#include <stddef.h>
#include <stdlib.h>

void swapNodes(struct Node** node1, struct Node** node2)
{
    struct Node* temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

int partition(struct Node** nodes, int low, int high)
{
    int pivot = -10000;
    if (nodes[high] != NULL)
        pivot = nodes[high]->freq;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (nodes[j] == NULL)
            continue;
        if (nodes[j]->freq > pivot) {
            i++;
            swapNodes(&nodes[i], &nodes[j]);
        }
    }

    swapNodes(&nodes[i + 1], &nodes[high]);
    return (i + 1);
}

void quickSort(struct Node** nodes, int low, int high)
{
    if (low < high) {
        int pi = partition(nodes, low, high);
        quickSort(nodes, low, pi - 1);
        quickSort(nodes, pi + 1, high);
    }
}