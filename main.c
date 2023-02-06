#include "cut.h"

extern int idle[NUM_OF_CORES][2], total[NUM_OF_CORES][2];

int main() {

    for (int i = 0; i < NUM_OF_CORES; i++) {
        idle[i][0] = 0;
        total[i][0] = 0;
    }
    pthread_t tid[3];
    pthread_create(&tid[0], NULL, Reader, NULL);
    pthread_create(&tid[1], NULL, Analyzer, NULL);
    pthread_create(&tid[2], NULL, Printer, NULL);

    for (int i = 0; i < NUM_OF_CORES; i++) {
        idle[i][0] = idle[i][1];
        total[i][0] = total[i][1];
    }

    sleep(1);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
}