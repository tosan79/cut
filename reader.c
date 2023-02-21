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
/*
void *Reader2(void *vargp) {
    stats_queue *sqp = (stats_queue *)vargp;
    char buffer[STAT_MAX_LEN];

    FILE* fp = fopen("out1", "r");
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

    // 2
    char buffer2[STAT_MAX_LEN];
    fp = fopen("out2", "r");
    c = fgetc(fp);
    i = 0;
    while (c != EOF) {
        buffer2[i] = c;
        c = fgetc(fp);
        i++;
    }
    fclose(fp);

    struct stats cpu2;
    p = strtok(buffer2, " ");
    for (int i = 0; i < NUM_OF_CORES; i++) {
        strcpy(cpu2.core[i], p);
        for (int j = user; j <= guest_nice; j++) {
            p = strtok(NULL, " \n");
            cpu2.value[i][j] = atoi(p);
        }
        p = strtok(NULL, " \n");
    }
    cpu2.next = NULL;
    sq_insert(sqp, &cpu2);

    // 3
    char buffer3[STAT_MAX_LEN];
    fp = fopen("out3", "r");
    c = fgetc(fp);
    i = 0;
    while (c != EOF) {
        buffer3[i] = c;
        c = fgetc(fp);
        i++;
    }
    fclose(fp);

    struct stats cpu3;
    p = strtok(buffer3, " ");
    for (int i = 0; i < NUM_OF_CORES; i++) {
        strcpy(cpu3.core[i], p);
        for (int j = user; j <= guest_nice; j++) {
            p = strtok(NULL, " \n");
            cpu3.value[i][j] = atoi(p);
        }
        p = strtok(NULL, " \n");
    }
    cpu3.next = NULL;
    sq_insert(sqp, &cpu3);

    // 4
    char buffer4[STAT_MAX_LEN];
    fp = fopen("out4", "r");
    c = fgetc(fp);
    i = 0;
    while (c != EOF) {
        buffer4[i] = c;
        c = fgetc(fp);
        i++;
    }
    fclose(fp);

    struct stats cpu4;
    p = strtok(buffer4, " ");
    for (int i = 0; i < NUM_OF_CORES; i++) {
        strcpy(cpu4.core[i], p);
        for (int j = user; j <= guest_nice; j++) {
            p = strtok(NULL, " \n");
            cpu4.value[i][j] = atoi(p);
        }
        p = strtok(NULL, " \n");
    }
    cpu4.next = NULL;
    sq_insert(sqp, &cpu4);

    // 5
    char buffer5[STAT_MAX_LEN];
    fp = fopen("out5", "r");
    c = fgetc(fp);
    i = 0;
    while (c != EOF) {
        buffer5[i] = c;
        c = fgetc(fp);
        i++;
    }
    fclose(fp);

    struct stats cpu5;
    p = strtok(buffer5, " ");
    for (int i = 0; i < NUM_OF_CORES; i++) {
        strcpy(cpu5.core[i], p);
        for (int j = user; j <= guest_nice; j++) {
            p = strtok(NULL, " \n");
            cpu5.value[i][j] = atoi(p);
        }
        p = strtok(NULL, " \n");
    }
    cpu5.next = NULL;
    sq_insert(sqp, &cpu5);

    // 6
    char buffer6[STAT_MAX_LEN];
    fp = fopen("out6", "r");
    c = fgetc(fp);
    i = 0;
    while (c != EOF) {
        buffer6[i] = c;
        c = fgetc(fp);
        i++;
    }
    fclose(fp);

    struct stats cpu6;
    p = strtok(buffer6, " ");
    for (int i = 0; i < NUM_OF_CORES; i++) {
        strcpy(cpu6.core[i], p);
        for (int j = user; j <= guest_nice; j++) {
            p = strtok(NULL, " \n");
            cpu6.value[i][j] = atoi(p);
        }
        p = strtok(NULL, " \n");
    }
    cpu6.next = NULL;
    sq_insert(sqp, &cpu6);

    return NULL;
}
*/
