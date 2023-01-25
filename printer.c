#include "cut.h"

extern int idle[NUM_OF_CORES][2], total[NUM_OF_CORES][2];
extern double use[NUM_OF_CORES];

void Printer() {
    printf("[cpu       ] usage: %f%%\n", use[0]);
    for (int i = 1; i < NUM_OF_CORES; i++)
        printf("[cpu core %d] usage: %f%%\n", i, use[i]);
}