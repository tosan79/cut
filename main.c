#include "cut.h"

int main() {
    pthread_t tid[3];
    stats_queue *sqp = sq_init();
    for (int i = 0; i < 4; i++) {
        pthread_create(&tid[0], NULL, Reader, (void *)sqp);
        pthread_create(&tid[1], NULL, Analyzer, (void *)sqp);
        sleep(1);
    }
    sq_print(sqp);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
}