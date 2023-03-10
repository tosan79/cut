#include "cut.h"

void *Reader(void *vargp) {
    stats_queue *sqp = (stats_queue *)vargp;
    char buffer[STAT_MAX_LEN];

    FILE* fp = fopen("/proc/stat", "r");
    char c = fgetc(fp);
    int i = 0;
    while (c != EOF) {
        buffer[i] = c;
        c = fgetc(fp);
        i++;
    }
    fclose(fp);

    struct stats cpu;
    char *p = strtok(buffer, " ");
    for (int i = 0; i < NUM_OF_CORES; i++) {
        strcpy(cpu.core[i], p);
        for (int j = user; j <= guest_nice; j++) {
            p = strtok(NULL, " \n");
            cpu.value[i][j] = atoi(p);
        }
        p = strtok(NULL, " \n");
    }
    cpu.next = NULL;
    
    sq_insert(sqp, &cpu);
    return NULL;
}