#include "cut.h"

int main() {
    pthread_t tid[3];
    stats_queue *sqp = sq_init();
    
    pthread_create(&tid[0], NULL, Reader2, (void *)sqp);
    sleep(1);
    for (int i = 0; i < 6; i++) {
        //pthread_create(&tid[0], NULL, Reader, (void *)sqp);
        pthread_create(&tid[1], NULL, Analyzer, (void *)sqp);
        pthread_create(&tid[2], NULL, Printer, (void *)sqp);
        sleep(1);
    }
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    sq_destroy(sqp);
}