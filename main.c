#include "cut.h"

int main() {
    pthread_t tid;
    stats_queue *sqp = sq_init();
    pthread_create(&tid, NULL, Reader, (void *)sqp);
    pthread_join(tid, NULL);
}