#include "cut.h"

void *Printer(void *vargp) {
    stats_queue *sqp = (stats_queue *)vargp;
    pthread_mutex_lock(&sqp->mutex);
    printf("[cpu]        usage: %f%%\n", sqp->first->usage[0]);
    for (int i = 1; i < NUM_OF_CORES; i++)
        printf("[cpu core %d] usage: %f%%\n", i, sqp->first->usage[i]);
    printf("\n");
    pthread_mutex_unlock(&sqp->mutex);
    sq_delete(sqp);
    return NULL;
}