#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

#define STAT_MAX_LEN 4000
#define FIELDS_LEN 10
#define NUM_OF_CORES 5
#define CORE_NAME_LEN 5
#define K 11

enum fields {user, nice1, system1, idle1, iowait, irq, softirq, steal, guest, guest_nice};

struct stats {
    int id;
    char core[NUM_OF_CORES][CORE_NAME_LEN];
    int value[NUM_OF_CORES][FIELDS_LEN];
    struct stats *next;
};

typedef struct {
    struct stats *first;
    struct stats *last;
    pthread_mutex_t mutex;
    sem_t slots, items;
    int size;
} stats_queue;

stats_queue *sq_init();
void sq_insert(stats_queue *qp, const struct stats *sp);
void sq_delete(stats_queue *qp);
void sq_print(stats_queue *qp);
//void sq_destroy(stats_queue *qp);

void *Reader(void *vargp);
//void *Analyzer(void *vargp);
//void *Printer(void *vargp);