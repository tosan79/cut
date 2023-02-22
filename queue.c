#include "cut.h"
int stats_id;

stats_queue *sq_init() {
    stats_queue *qp = (stats_queue *)malloc(sizeof(stats_queue));
    qp->first = qp->last = NULL;
    pthread_mutex_init(&qp->mutex, NULL);
    sem_init(&qp->items, 0, 0);
    sem_init(&qp->slots, 0, K);
    qp->size = 0;
    stats_id = 0;
    //printf("queue initialized.\n");
    return qp;
}

void sq_insert(stats_queue *qp, const struct stats *sp) {
    int t = qp->size;
    sem_wait(&qp->slots);
    struct stats *new_sp = (struct stats *)malloc(sizeof(struct stats));
    new_sp->id = stats_id++;
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
    //printf("inserted item on queue. queue size: %d\n", qp->size);
    assert(qp->size == t + 1);
}

void sq_delete(stats_queue *qp) {
    if (qp == NULL)
        return;
    int t = qp->size;
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
    //printf("deleted (first) item from queue.\n");
    assert(qp->size == t - 1);
}

void sq_print(stats_queue *qp) {
    struct stats *sp = qp->first;
    if (sp == NULL) {
        printf("stats queue empty.\n");
        return;
    }
    printf("printing queue:\n");
    do {
        printf("[%d]\n", sp->id);
        for (int i = 0; i < NUM_OF_CORES; i++) {
            printf("%s ", sp->core[i]);
            for (int j = user; j <= guest_nice; j++)
                printf("%d ", sp->value[i][j]);
            printf("usage: %f%%\n", sp->usage[i]);
        }
        printf("\n");
        sp = sp->next;
    } while (sp != NULL);
}

void sq_destroy(stats_queue *qp) {
    //printf("destroying queue.\n");
    if (qp == NULL)
        return;
    while (qp->first != NULL) {
        struct stats *sp = qp->first;
        qp->first = qp->first->next;
        free(sp);
    }
    free(qp);
}

int sq_is_empty(stats_queue *qp) {
    if (qp == NULL)
	return -1;
    return qp->first == NULL;
}
