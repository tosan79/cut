#include "cut.h"

void *Analyzer(void *vargp) {
    stats_queue *sqp = (stats_queue *)vargp;
    struct stats *cpu[2];
    if (sqp->size < 2)
        return NULL;

    cpu[0] = sqp->first;
    cpu[1] = sqp->first->next;

    int idle[2][NUM_OF_CORES], total[2][NUM_OF_CORES]; // a[x][] - values for cpu[x]
    double total_dif[NUM_OF_CORES], idle_dif[NUM_OF_CORES];
    for (int i = 0; i < NUM_OF_CORES; i++) {
        for (int k = 0; k < 2; k++) {
            idle[k][i] = cpu[k]->value[i][idle1] + cpu[k]->value[i][iowait];
            total[k][i] = 0;
            for (int j = user; j <= guest_nice; j++)
                total[k][i] += cpu[k]->value[i][j];
        }
        total_dif[i] = total[1][i] - total[0][i];
        idle_dif[i] = idle[1][i] - idle[0][i];
        cpu[1]->usage[i] = (total_dif[i] - idle_dif[i]) * 100.0 / total_dif[i];
    }
    return NULL;
}