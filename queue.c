#include "cut.h"

stats_queue *sq_init() {
    stats_queue *qp = (stats_queue *)malloc(sizeof(stats_queue));
    qp->first = qp->last = NULL;
    pthread_mutex_init(&qp->mutex, NULL);
    sem_init(&qp->items, 0, 0);
    sem_init(&qp->slots, 0, 1);
    qp->size = 0;
    return qp;
}

void sq_destory(stats_queue *qp) {
    free(qp);
}

void queue_insert(stats_queue *qp, const struct stats *sp) {
    struct stats *new_sp = (struct stats *)malloc(sizeof(struct stats));
    for (int i = 0; i < NUM_OF_CORES; i++) {
        strcpy(new_sp->core[i], sp->core[i]);
        for (int j = user; j <= guest_nice; j++)
            new_sp->value[i][j] = sp->value[i][j];
    }
    new_sp->next = NULL;
    
    if (qp->first == NULL)
        qp->first = qp->last = new_sp;
    else {
        qp->last->next = new_sp;
        qp->last = new_sp;
    }
    qp->size++;
}