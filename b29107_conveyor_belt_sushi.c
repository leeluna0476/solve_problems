#include <stdio.h>
#include <stdlib.h>

#define QMAX 10
typedef struct node {
	int data;
	struct node *link;
} node_t;

typedef struct queue {
	node_t *rear;
} queue_t;

queue_t orders[200001];

void init_queue(queue_t *q) {
	q->rear = NULL;
}

int is_empty_queue(queue_t *q) {
	return q->rear == NULL;
}

node_t *create_node(int val) {
	node_t *n = (node_t *)malloc(sizeof(node_t));
	n->data = val;
	n->link = NULL;
	return n;
}

int free_node(node_t *node) {
	int e = node->data;
	free(node);
	return e;
}

void enqueue(queue_t *q, int val) {
	node_t *n = create_node(val);
	if (is_empty_queue(q)) {
		q->rear = n;
		n->link = n;
	}
	else {
		n->link = q->rear->link;
		q->rear->link = n;
		q->rear = n;
	}
}

int dequeue(queue_t *q) {
	if (is_empty_queue(q)) {
		return -1;
	}
	else {
		node_t *front = q->rear->link;
		q->rear->link = front->link;
		if (q->rear == front) {
			q->rear = NULL;
		}
		return free_node(front);
	}
}

int main(void) {
	int N, M;
	scanf("%d %d", &N, &M);

	for (int i = 1; i <= N; ++i) {
		int K;
		scanf("%d", &K);
		for (int j = 0; j < K; ++j) {
			int sushi;
			scanf("%d", &sushi);
			enqueue(&orders[sushi], i);
		}
	}

	int sushi_per_cust[100001] = { 0, };
	for (int i = 0; i < M; ++i) {
		int sushi;
		scanf("%d", &sushi);
		if (!is_empty_queue(&orders[sushi])) {
			int c = dequeue(&orders[sushi]);
			++sushi_per_cust[c];
		}
	}

	for (int i = 1; i <= N; ++i) {
		printf("%d ", sushi_per_cust[i]);
	}
	printf("\n");
}
