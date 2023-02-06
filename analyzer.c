#include "cut.h"

extern struct stats cpu;
int idle[NUM_OF_CORES][2], total[NUM_OF_CORES][2];
double use[NUM_OF_CORES];

void *Analyzer(void *vargp) {
    for (int i = 0; i < NUM_OF_CORES; i++) {
        idle[i][1] = cpu.value[i][idle1] + cpu.value[i][iowait];
        total[i][1] = 0;
        for (int j = user; j <= guest_nice; j++) {
            total[i][1] += cpu.value[i][j];
        }
        
        double x = total[i][1] - total[i][0];
        double y = idle[i][1] - idle[i][0]; 
        use[i] = (x - y) * 100.0 / x;
    }
    return NULL;
}