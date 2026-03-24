#include <stdio.h>

#define QMAX 100001
typedef struct queue {
	int storage[QMAX];
	int front;
	int rear;
} queue_t;

queue_t q;
int N;
int max_size;
int tail = 100001;

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

// enqueue하면서 max_size, (그 때 맨 뒷사람) update
int main(void) {
	scanf("%d", &N);

	init_queue(&q);
	for (int i = 0; i < N; ++i) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			int person;
			scanf("%d", &person);
			enqueue(&q, person);
			int qsize = size_queue(&q);
			if (qsize >= max_size) {
				if (qsize == max_size) {
					tail = tail < person ? tail : person;
				}
				else {
					tail = person;
				}
				max_size = qsize;
			}
		}
		else {
			dequeue(&q);
		}
	}

	printf("%d %d\n", max_size, tail);
}
