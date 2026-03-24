#include <stdio.h>

typedef struct pos {
	int x;
	int y;
} pos_t;

#define QMAX 10001
typedef struct queue {
	pos_t storage[QMAX];
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

void enqueue(queue_t *q, pos_t val) {
	if (is_full_queue(q)) {
		return;
	}
	else {
		q->rear = (q->rear + 1) % QMAX;
		q->storage[q->rear] = val;
	}
}

pos_t dequeue(queue_t *q) {
	pos_t r = { -1, -1 };
	if (!is_empty_queue(q)) {
		q->front = (q->front + 1) % QMAX;
		r = q->storage[q->front];
	}
	return r;
}

int n, m;
#define MAX 100
int map[MAX][MAX];

int in_range(pos_t *pos) {
	return pos->x >= 0 && pos->x < m && pos->y >= 0 && pos->y < n;
}

int bfs(void) {
	queue_t q;
	init_queue(&q);

	int diff[4][2] = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };
	pos_t pos = { 0, 0 };
	enqueue(&q, pos);
	map[0][0] = 1;
	while (!is_empty_queue(&q)) {
		pos = dequeue(&q);
		if (pos.x + 1 == m && pos.y + 1 == n) {
			break;
		}
		for (int i = 0; i < 4; ++i) {
			pos_t npos = { pos.x + diff[i][0], pos.y + diff[i][1] };
			if (in_range(&npos) && map[npos.y][npos.x] == 1) {
				enqueue(&q, npos);
				map[npos.y][npos.x] = map[pos.y][pos.x] + 1;
			}
		}
		map[pos.y][pos.x] = 0;
	}

	return map[n - 1][m - 1];
}

int main(void) {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			char x;
			scanf(" %c", &x);
			map[i][j] = x - '0';
		}
	}

	printf("%d\n", bfs());
}
