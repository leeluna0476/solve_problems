#include <stdio.h>
#include <stdlib.h>

#define QMAX 500001
typedef struct queue {
	int storage[QMAX];
	int front;
	int rear;
} queue_t;

void error(char *errmsg) {
	fprintf(stderr, "%s", errmsg);
	exit(1);
}
void init_q(queue_t *q) {
	q->front = 0;
	q->rear = 0;
}

int is_empty_q(queue_t *q) {
	return q->front == q->rear;
}

int is_full_q(queue_t *q) {
	return (q->rear + 1) % QMAX == q->front;
}

void enqueue(queue_t *q, int data) {
	if (is_full_q(q)) {
		error("Overflow\n");
	}
	else {
		q->rear = (q->rear + 1) % QMAX;
		q->storage[q->rear] = data;
	}
}

int dequeue(queue_t *q) {
	if (is_empty_q(q)) {
		error("Underflow\n");
	}
	else {
		q->front = (q->front + 1) % QMAX;
		return q->storage[q->front];
	}
}

#define HMAX 500000
typedef struct heap {
	int storage[HMAX];
	int size;
} heap_t;

#define PARENT(i) ((i - 1) >> 1)
#define LEFT(i) ((i << 1) + 1)
#define RIGHT(i) ((i << 1) + 2)

void init_heap(heap_t *ht) {
	ht->size = 0;
}

char is_empty_heap(heap_t *ht) {
	return !ht->size;
}

char is_full_heap(heap_t *ht) {
	return ht->size == HMAX;
}

void push_minheap(heap_t *ht, int val) {
	if (is_full_heap(ht)) {
		return;
	}
	ht->storage[ht->size] = val;
	int i = ht->size++;
	while (i) {
		int parent = PARENT(i);
		if (ht->storage[parent] <= ht->storage[i]) {
			break;
		}
		int tmp = ht->storage[i];
		ht->storage[i] = ht->storage[parent];
		ht->storage[parent] = tmp;
		i = parent;
	}
}

int pop_minheap(heap_t *ht) {
	if (is_empty_heap(ht)) {
		return 0;
	}
	int ret = ht->storage[0];
	ht->storage[0] = ht->storage[--ht->size];
	int i = 0;
	while (LEFT(i) < ht->size) {
		int child = RIGHT(i) == ht->size ? LEFT(i) : (ht->storage[LEFT(i)] <= ht->storage[RIGHT(i)] ? LEFT(i) : RIGHT(i));
		if (ht->storage[i] <= ht->storage[child]) {
			break;
		}
		int tmp = ht->storage[i];
		ht->storage[i] = ht->storage[child];
		ht->storage[child] = tmp;
		i = child;
	}
	return ret;
}

void heap_sort(queue_t *q) {
	heap_t h;
	init_heap(&h);
	while (!is_empty_q(q)) {
		push_minheap(&h, dequeue(q));
	}
	while (!is_empty_heap(&h)) {
		printf("%d ", pop_minheap(&h));
	}
	printf("\n");
}

void print_result(queue_t *q) {
	if (is_empty_q(q)) {
		printf("None\n");
	}
	else {
		heap_sort(q);
	}
}

#define ADD_MENU(b, a) (menu[b][(a) / 8] |= 1 << ((a) % 8))
#define CHECK_MENU(b, a) (menu[b][(a) / 8] >> ((a) % 8) & 1)

int main(void) {
	int n;
	scanf("%d", &n);

	queue_t C, A, B;
	init_q(&C);
	init_q(&A);
	init_q(&B);
	char menu[2][500000 / 8] = { 0, };

	for (int i = 0; i < n; ++i) {
		int d;
		scanf("%d", &d);
		if (d == 1) {
			int a, b;
			scanf("%d %d", &a, &b);
			ADD_MENU(b - 1, a - 1);
			enqueue(&C, a);
		}
		else {
			int b;
			scanf("%d", &b);
			int c = dequeue(&C);
			if (CHECK_MENU(b - 1, c - 1)) {
				enqueue(&A, c);
			}
			else {
				enqueue(&B, c);
			}
		}
	}

	print_result(&A);
	print_result(&B);
	print_result(&C);
}
