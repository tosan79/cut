#include "cut.h"

char buffer[STAT_MAX_LEN];
struct stats cpu[NUM_OF_CORES];

void Reader() {
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
        strcpy(cpu[i].core, p);
        for (int j = user; j <= guest_nice; j++) {
            p = strtok(NULL, " \n");
            cpu[i].value[j] = atoi(p);
        }
        p = strtok(NULL, " \n");
    }
}