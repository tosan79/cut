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

void sq_insert(stats_queue *qp, const struct stats *sp) {
    sem_wait(&qp->slots);
    struct stats *new_sp = (struct stats *)malloc(sizeof(struct stats));
    for (int i = 0; i < NUM_OF_CORES; i++) {
        strcpy(new_sp->core[i], sp->core[i]);
        for (int j = user; j <= guest_nice; j++)
            new_sp->value[i][j] = sp->value[i][j];
    }
    new_sp->next = NULL;
    
    pthread_mutex_lock(&qp->mutex);
    if (qp->first == NULL)
        qp->first = qp->last = new_sp;
    else {
        qp->last->next = new_sp;
        qp->last = new_sp;
    }
    qp->size++;
    pthread_mutex_unlock(&qp->mutex);
    sem_post(&qp->items);
}

void sq_delete(stats_queue *qp) {
    if (qp == NULL)
        return;
    sem_wait(&qp->items);
    pthread_mutex_lock(&qp->mutex);
    struct stats *sp = qp->first;
    if (qp->first == qp->last)
        qp->first = qp->last = NULL;
    else
        qp->first = sp->next;
    qp->size--;
    free(sp);
    pthread_mutex_unlock(&qp->mutex);
    sem_post(&qp->slots);
}

void sq_print(stats_queue *qp) {
    struct stats *sp = qp->first;
    do {
        for (int i = 0; i < NUM_OF_CORES; i++) {
            printf("%s ", sp->core[i]);
            for (int j = user; j <= guest_nice; j++)
                printf("%d ", sp->value[i][j]);
            printf("\n");
        }
        sp = qp->first->next;
    } while (sp->next != NULL);
}