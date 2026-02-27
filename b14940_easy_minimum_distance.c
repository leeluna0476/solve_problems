#include <stdio.h>

#define MAX 1000
#define QMAX 1000001

typedef struct pos {
	int x;
	int y;
} pos_t;

typedef struct queue {
	pos_t storage[QMAX];
	int front;
	int back;
} queue_t;

int n, m, map[MAX][MAX], answer[MAX][MAX];

void init(queue_t *q) {
	q->front = 0;
	q->back = 0;
}

char is_empty(queue_t *q) {
	return q->front == q->back;
}

char is_full(queue_t *q) {
	return (q->back + 1) % QMAX == q->front;
}

void enqueue(queue_t *q, pos_t val) {
	if (!is_full(q)) {
		q->back = (q->back + 1) % QMAX;
		q->storage[q->back] = val;
	}
}

pos_t dequeue(queue_t *q) {
	pos_t val = { -1, -1 };
	if (!is_empty(q)) {
		q->front = (q->front + 1) % QMAX;
		val = q->storage[q->front];
	}
	return val;
}

pos_t find_destination(void) {
	pos_t dst = { -1, -1 };
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (map[i][j] == 2) {
				dst.x = j;
				dst.y = i;
				return dst;
			}
		}
	}
	return dst;
}

char in_range(pos_t *pos) {
	return pos->x >= 0 && pos->x < m && pos->y >= 0 && pos->y < n;
}

void bfs(pos_t dst) {
	answer[dst.y][dst.x] = 0;
	map[dst.y][dst.x] = 0;

	int diff[4][2] = {
		{ 0, -1 },
		{ 0, 1 },
		{ -1, 0 },
		{ 1, 0 },
	};

	queue_t q;
	init(&q);
	enqueue(&q, dst);
	while (!is_empty(&q)) {
		pos_t pos = dequeue(&q);
		int distance = answer[pos.y][pos.x];
		for (int i = 0; i < 4; ++i) {
			pos_t npos = { pos.x + diff[i][0], pos.y + diff[i][1] };
			if (in_range(&npos) && map[npos.y][npos.x] == 1) {
				answer[npos.y][npos.x] = distance + 1;
				map[npos.y][npos.x] = 0;
				enqueue(&q, npos);
			}
		}
	}
}

int main(void) {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			scanf("%d", &map[i][j]);
		}
	}

	pos_t dst = find_destination();
	bfs(dst);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (map[i][j] && !answer[i][j]) {
				printf("%d ", -1);
			}
			else {
				printf("%d ", answer[i][j]);
			}
		}
		printf("\n");
	}
}
