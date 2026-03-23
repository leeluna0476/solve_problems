#include <stdio.h>

#define MAXQ 3
typedef struct queue {
	unsigned long long storage[MAXQ];
	int front;
	int rear;
} queue_t;

queue_t q;

void init(void) {
	q.front = 0;
	q.rear = 0;
}

int is_empty(void) {
	return q.front == q.rear;
}

int is_full(void) {
	return (q.rear + 1) % MAXQ == q.front;
}

void enqueue(unsigned long long e) {
	if (is_full()) {
		return;
	}
	else {
		q.rear = (q.rear + 1) % MAXQ;
		q.storage[q.rear] = e;
	}
}

unsigned long long dequeue(void) {
	if (is_empty()) {
		return -1ULL;
	}
	else {
		q.front = (q.front + 1) % MAXQ;
		return q.storage[q.front];
	}
}

unsigned long long peek(void) {
	if (is_empty()) {
		return -1ULL;
	}
	else {
		return q.storage[(q.front + 1) % MAXQ];
	}
}

unsigned long long fibonacci(int n) {
	init();
	enqueue(0);
	enqueue(1);
	for (int i = 2; i <= n; ++i) {
		unsigned long long n1 = dequeue();
		unsigned long long n2 = peek();
		enqueue(n1 + n2);
	}
	dequeue();
	return dequeue();
}

int main(void) {
	int n;
	scanf("%d", &n);
	printf("%llu\n", fibonacci(n));
}
