#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

#define STAT_MAX_LEN 4000
#define FIELDS_LEN 10
#define NUM_OF_CORES 5

enum fields {user, nice1, system1, idle1, iowait, irq, softirq, steal, guest, guest_nice};

struct stats {
    char *core[NUM_OF_CORES];
    int value[NUM_OF_CORES][FIELDS_LEN];
};

typedef struct {
    struct stats *s;
    int front, rear;
    pthread_mutex_t mutex;
    sem_t slots, items;
} q;

void *Reader(void *vargp);
void *Analyzer(void *vargp);
void *Printer(void *vargp);