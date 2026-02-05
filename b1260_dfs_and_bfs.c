#include <stdio.h>

#define MAX 1000
#define MAXDQ 1001

typedef struct _dequeue_t {
	short storage[MAXDQ];
	int front;
	int rear;
} _dequeue_t;

void init(_dequeue_t *dq) {
	dq->front = 0;
	dq->rear = 0;
}

int is_empty(_dequeue_t *dq) {
	return dq->front == dq->rear;
}

int is_full(_dequeue_t *dq) {
	return dq->front == (dq->rear + 1) % MAXDQ;
}

void add_rear(_dequeue_t *dq, int e) {
	if (!is_full(dq)) {
		dq->rear = (dq->rear + 1) % MAXDQ;
		dq->storage[dq->rear] = e;
	}
}

int delete_front(_dequeue_t *dq) {
	if (is_empty(dq)) {
		return -1;
	}
	else {
		dq->front = (dq->front + 1) % MAXDQ;
		return dq->storage[dq->front];
	}
}

int delete_rear(_dequeue_t *dq) {
	if (is_empty(dq)) {
		return -1;
	}
	else {
		int ret = dq->storage[dq->rear];
		dq->rear = (dq->rear - 1 + MAXDQ) % MAXDQ;
		return ret;
	}
}

void dfs_s(char (*graph)[MAX], int N, int v) {
	static char visited[1000] = { 0, };
	if (visited[v]) {
		return;
	}
	visited[v] = 1;
	printf("%d ", v + 1);
	for (int i = 0; i < N; ++i) {
		if (graph[v][i] && !visited[i]) {
			dfs_s(graph, N, i);
		}
	}
}

void dfs(char (*graph)[MAX], int N, int V) {
	dfs_s(graph, N, V - 1);
	printf("\n");
}

void bfs(char (*graph)[MAX], int N, int V) {
	char visited[MAX] = { 0, };
	_dequeue_t q;
	init(&q);
	int v = V - 1;
	while (v != -1) {
		visited[v] = 1;
		printf("%d ", v + 1);
		for (int i = 0; i < N; ++i) {
			if (i == v) {
				continue;
			}

			if (graph[v][i] && !visited[i]) {
				visited[i] = 1;
				add_rear(&q, i);
			}
		}
		v = delete_front(&q);
	}
	printf("\n");
}

int main(void) {
	int N, M, V;
	scanf("%d %d %d", &N, &M, &V);

	char graph[MAX][MAX] = { 0, };
	for (int m = 0; m < M; ++m) {
		int a, b;
		scanf("%d %d", &a, &b);
		graph[a - 1][b - 1] = 1;
		graph[b - 1][a - 1] = 1;
	}

	dfs(graph, N, V);
	bfs(graph, N, V);
}
