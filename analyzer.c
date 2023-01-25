#include "cut.h"

extern struct stats cpu[NUM_OF_CORES];

int idle[NUM_OF_CORES][2], total[NUM_OF_CORES][2];
double use[NUM_OF_CORES];

void *Analyzer(void *vargp) {
    for (int i = 0; i < NUM_OF_CORES; i++) {
        idle[i][1] = cpu[i].value[idle1] + cpu[i].value[iowait];
        total[i][1] = 0;
        for (int j = user; j <= guest_nice; j++) {
            total[i][1] += cpu[i].value[j];
        }
        
        double x = total[i][1] - total[i][0];
        double y = idle[i][1] - idle[i][0]; 
        use[i] = (x - y) * 100.0 / x;
    }
}