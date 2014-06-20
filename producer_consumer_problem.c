#include "csapp.h"

#define NITERS 5

void *producer(void *arg);
void *consumer(void *arg);

struct {
	int buf;    // 공유 버퍼
	sem_t full; // 세마포어
	sem_t empty;
} shared;

int main() {
	pthread_t tid_producer;
	pthread_t tid_consumer;
	struct timeval start_timeval, end_timeval; // timeval은 us단위. clock_t는 초단위

	Sem_init(&shared.empty, 0, 1); // 세마포어 초기화
	Sem_init(&shared.full, 0, 0);

	gettimeofday(&start_timeval, NULL); // 시작 시각
	Pthread_create(&tid_producer, NULL, producer, NULL);//쓰레드 생성
	Pthread_create(&tid_consumer, NULL, consumer, NULL);
	Pthread_join(tid_producer, NULL);
	Pthread_join(tid_consumer, NULL);
	gettimeofday(&end_timeval, NULL); // 종료 시각 
	printf("경과 시간: %ld us\n", (end_timeval.tv_sec*1000000 + end_timeval.tv_usec) - (start_timeval.tv_sec*1000000 + start_timeval.tv_usec));

	exit(0);
}

void *producer(void *arg) {
	int i, item;

	for (i=0; i<NITERS; i++) {
		item = i;
		printf("%d produced %d\n", i, item);

		P(&shared.empty);
		shared.buf = item; //버퍼에 쓰기
		V(&shared.full);
	}
	return NULL;
}

void *consumer(void *arg) {
	int i, item;

	for (i=0; i<NITERS; i++) {
		P(&shared.full);
		item = shared.buf; //버퍼에서 읽기
		V(&shared.empty);
		printf("%d consumed %d\n", i, item);
	}
	return NULL;
}
