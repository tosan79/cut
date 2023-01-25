#include "cut.h"

extern int idle[NUM_OF_CORES][2], total[NUM_OF_CORES][2];

int main() {
    for (int i = 0; i < NUM_OF_CORES; i++) {
        idle[i][0] = 0;
        total[i][0] = 0;
    }
    
    Reader();
    Analyzer();
    Printer();
}