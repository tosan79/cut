#include "cut.h"

enum fields {user, nice, system1, idle, iowait, \
    irq, softirq, steal, guest, guest_nice};

/*
Idle = idle + iowait
NonIdle = user + nice + system1 + irq + softirq + steal
Total = Idle + NonIdle
cpu% = (Total - Total_0) - (Idle - Idle_0) / (Total - Total_0)
*/

struct stats {
    char core[NUM_OF_CORES];
    int value[FIELDS_LEN];
};

extern char buffer[STAT_MAX_LEN];

void Analyzer() {
    printf("%s\n", buffer);

    struct stats cpu[NUM_OF_CORES];
    char *p = strtok(buffer, " ");
    for (int i = 0; i < NUM_OF_CORES; i++) {
        strcpy(cpu[i].core, p);
        for (int j = user; j <= guest_nice; j++) {
            p = strtok(NULL, " \n");
            cpu[i].value[j] = atoi(p);
        }
        p = strtok(NULL, " \n");

        printf("%s ", cpu[i].core);
        for (int j = user; j <= guest_nice; j++)
            printf("%d ", cpu[i].value[j]);
        printf("\n");
    }
}