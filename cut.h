#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define STAT_MAX_LEN 4000
#define FIELDS_LEN 10
#define NUM_OF_CORES 5

enum fields {user, nice, system1, idle1, iowait, irq, softirq, steal, guest, guest_nice};

struct stats {
    char core[NUM_OF_CORES];
    int value[FIELDS_LEN];
};

void Reader();
void Analyzer();
void Printer();