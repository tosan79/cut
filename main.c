#include "cut.h"

int main() {
    pthread_t tid[3];
    stats_queue *sqp = sq_init();
    
    pthread_create(&tid[0], NULL, Reader, (void *)sqp);
    sleep(1);

    for (int i = 0; i < K; i++) {
	pthread_create(&tid[0], NULL, Reader, (void *)sqp);
	usleep(500000);
	pthread_create(&tid[1], NULL, Analyzer, (void *)sqp);
	usleep(500000);
	pthread_create(&tid[2], NULL, Printer, (void *)sqp);
    }
    
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    sq_destroy(sqp);
}
