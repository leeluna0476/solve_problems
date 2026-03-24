#include <stdio.h>
#include <string.h>

#define QMAX 2000001
typedef struct queue {
	int storage[QMAX];
	int front;
	int rear;
} queue_t;

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

int front(queue_t *q) {
	if (is_empty_queue(q)) {
		return -1;
	}
	else {
		return q->storage[(q->front + 1) % QMAX];
	}
}

int back(queue_t *q) {
	if (is_empty_queue(q)) {
		return -1;
	}
	else {
		return q->storage[q->rear];
	}
}

int size_queue(queue_t *q) {
	return (q->rear - q->front + QMAX) % QMAX;
}

int main(void) {
	int N;
	scanf("%d", &N);
	char cmd[6];
	int x;
	queue_t q;
	init_queue(&q);
	for (int i = 0; i < N; ++i) {
		scanf("%s", cmd);
		if (!strcmp(cmd, "push")) {
			scanf("%d", &x);
			enqueue(&q, x);
		}
		else if (!strcmp(cmd, "pop")) {
			printf("%d\n", dequeue(&q));
		}
		else if (!strcmp(cmd, "size")) {
			printf("%d\n", size_queue(&q));
		}
		else if (!strcmp(cmd, "empty")) {
			printf("%d\n", is_empty_queue(&q));
		}
		else if (!strcmp(cmd, "front")) {
			printf("%d\n", front(&q));
		}
		else {
			printf("%d\n", back(&q));
		}
	}
}
