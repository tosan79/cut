#include "cut.h"

void *Reader(void *vargp) {
    stats_queue *sqp = (stats_queue *)vargp;
    printf("starting reading.\n");
    for (int k = 0; k < 3; k++) {
        struct stats cpu; // = (struct stats *)malloc(sizeof(struct stats));
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

        char *p = strtok(buffer, " ");
        for (int i = 0; i < NUM_OF_CORES; i++) {
            strcpy(cpu.core[i], p);
            for (int j = user; j <= guest_nice; j++) {
                p = strtok(NULL, " \n");
                cpu.value[i][j] = atoi(p);
            }
            p = strtok(NULL, " \n");
        }
        
        sq_insert(sqp, &cpu);
        sleep(1);
    }
    sq_print(sqp);
    return NULL;
}