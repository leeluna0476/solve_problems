#include <stdio.h>

#define MAX 10
#define MAX_N 1024

typedef struct queue {
	short storage[MAX_N];
	short front;
	short back;
} queue_t;

void init_queue(queue_t *q) {
	q->front = 0;
	q->back = 0;
}

char is_full(queue_t *q) {
	return (q->back + 1) % MAX_N == q->front;
}

char is_empty(queue_t *q) {
	return q->front == q->back;
}

void push_back(queue_t *q, short val) {
	if (!is_full(q)) {
		q->back = (q->back + 1) % MAX_N;
		q->storage[q->back] = val;
	}
}

short pop_front(queue_t *q) {
	if (!is_empty(q)) {
		q->front = (q->front + 1) % MAX_N;
		return q->storage[q->front];
	}
	else {
		return -1;
	}
}

short qsize(queue_t *q) {
	return (q->back - q->front + MAX_N) % MAX_N;
}

void print_binary_tree(short *tree, short n) {
	queue_t q;
	init_queue(&q);
	short level = 1;

	n >>= 1;
	push_back(&q, n);
	while (!is_empty(&q)) {
		short node = pop_front(&q);
		printf("%hd ", tree[node]);
		if (n) {
			short diff = n - (n >> 1);
			push_back(&q, node - diff);
			push_back(&q, node + diff);
		}

		if (qsize(&q) == 1 << level) {
			printf("\n");
			++level;
			n >>= 1;
		}
	}
	printf("\n");
}

int main(void) {
	short k;
	scanf("%hd", &k);
	short n = (1 << k) - 1;
	short tree[(1 << MAX) - 1];
	for (short i = 0; i < n; ++i) {
		scanf("%hd", &tree[i]);
	}

	print_binary_tree(tree, n);
}
