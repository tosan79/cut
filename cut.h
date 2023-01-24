#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define STAT_MAX_LEN 4000
#define FIELDS_LEN 10
#define NUM_OF_CORES 5

void Reader();
void Analyzer();