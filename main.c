#include "cut.h"

stats_queue *sqp;
struct stats cpu;

int main() {
    pthread_t tid;    
    sqp = sq_init();
    sq_print(sqp);
    while (1) {
        pthread_create(&tid, NULL, Reader, NULL);
        pthread_join(tid, NULL);
        sleep(1);
    }
    /* testing the insert
    sq_print(sqp);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            cpu.core[i][j] = 'x';
            cpu.value[i][j] = 1;
        }
        cpu.core[i][4] = '\0';
        for (int j = 4; j < 10; j++)
            cpu.value[i][j] = 1;
    }
    sq_insert(sqp, &cpu);
    sq_print(sqp); */
}