#include "cut.h"

extern double use[NUM_OF_CORES];

void *Printer(void *vargp) {
    printf("[cpu]        usage: %f%%\n", use[0]);
    for (int i = 1; i < NUM_OF_CORES; i++)
        printf("[cpu core %d] usage: %f%%\n", i, use[i]);
    printf("\n");
    return NULL;
}