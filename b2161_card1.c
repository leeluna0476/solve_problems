#include <stdio.h>

#define QMAX 1001
typedef struct queue {
	int storage[QMAX];
	int front;
	int rear;
} queue_t;

queue_t q;
int N;

void init_queue(queue_t *q) {
	q->front = 0;
	q->rear = 0;
}

int is_empty_queue(queue_t *q) {
	return q->front == q->rear;
}

int is_full_queue(queue_t *q) {
	return (q->rear + 1) % QMAX == q->front;
}

void enqueue(queue_t *q, int val) {
	if (is_full_queue(q)) {
		return;
	}
	else {
		q->rear = (q->rear + 1) % QMAX;
		q->storage[q->rear] = val;
	}
}

int dequeue(queue_t *q) {
	if (is_empty_queue(q)) {
		return -1;
	}
	else {
		q->front = (q->front + 1) % QMAX;
		return q->storage[q->front];
	}
}

int size_queue(queue_t *q) {
	return (q->rear - q->front + QMAX) % QMAX;
}

int main(void) {
	scanf("%d", &N);

	init_queue(&q);
	for (int i = 1; i <= N; ++i) {
		enqueue(&q, i);
	}

	while (size_queue(&q) > 1) {
		printf("%d ", dequeue(&q));
		enqueue(&q, dequeue(&q));
	}

	printf("%d\n", dequeue(&q));
}
