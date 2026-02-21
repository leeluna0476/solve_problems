#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
#define QMAX 1000000

typedef struct pos {
	int broken;
	int step;
	int x;
	int y;
} pos_t;

typedef struct queue {
	pos_t *storage; // 12MB
	int front;
	int back;
} queue_t;

queue_t q;
char **map; // 1MB
int ***route; // 8MB
int n;
int m;
char diff[4][2] = {
	{ 0, -1 },
	{ 0, 1 },
	{ -1, 0 },
	{ 1, 0 },
};

void init_queue(queue_t *q) {
	q->storage = calloc(QMAX, sizeof(pos_t));
	q->front = 0;
	q->back = 0;
}

char is_empty(queue_t *q) {
	return q->front == q->back;
}

char is_full(queue_t *q) {
	return (q->back + 1) % QMAX == q->front;
}

void push_back(queue_t *q, pos_t pos) {
	if (!is_full(q)) {
		q->back = (q->back + 1) % QMAX;
		q->storage[q->back] = pos;
	}
}

pos_t pop_front(queue_t *q) {
	pos_t ret = { 0, 0, -1, -1 };
	if (!is_empty(q)) {
		q->front = (q->front + 1) % QMAX;
		ret = q->storage[q->front];
	}
	return ret;
}

void remove_queue(queue_t *q) {
	free(q->storage);
}

char is_in_map(pos_t pos) {
	return pos.x >= 0 && pos.x < m && pos.y >= 0 && pos.y < n;
}

char move(pos_t *npos, int broken) {
	if (!map[npos->y][npos->x]) {
		if (!route[npos->y][npos->x][broken]) {
			route[npos->y][npos->x][broken] = 1;
			npos->broken = broken;
			return 1;
		}
	}
	else if (!broken) {
		if (!route[npos->y][npos->x][1]) {
			route[npos->y][npos->x][1] = 1;
			npos->broken = 1;
			return 1;
		}
	}
	return 0;
}

int bfs(void) {
	char diff[4][2] = {
		{ 0, -1 },
		{ 0, 1 },
		{ -1, 0 },
		{ 1, 0 },
	};
	pos_t pos = pop_front(&q);
	route[0][0][0] = 1;
	int answer = -1;
	while (pos.x != -1) {
		if (pos.x == m - 1 && pos.y == n - 1) {
			answer = answer == -1 || pos.step < answer ? pos.step : answer;
		}
		for (int i = 0; i < 4; ++i) {
			pos_t npos = { 0, pos.step + 1, pos.x + diff[i][0], pos.y + diff[i][1] };
			if (is_in_map(npos) && move(&npos, pos.broken)) {
				push_back(&q, npos);
			}
		}
		pos = pop_front(&q);
	}
	return answer;
}

int main(void) {
	init_queue(&q);

	scanf("%d %d", &n, &m);
	map = malloc(sizeof(char *) * n);
	route = malloc(sizeof(int **) * n);
	for (int i = 0; i < n; ++i) {
		map[i] = malloc(sizeof(char) * m);
		route[i] = malloc(sizeof(int *) * m);
		getchar();
		for (int j = 0; j < m; ++j) {
			map[i][j] = getchar() - '0';
			route[i][j] = calloc(2, sizeof(int));
		}
	}

	pos_t pos = { 0, 1, 0, 0 };
	push_back(&q, pos);
	printf("%d\n", bfs());

	for (int i = 0; i < n; ++i) {
		free(map[i]);
		for (int j = 0; j < m; ++j) {
			free(route[i][j]);
		}
		free(route[i]);
	}
	free(map);
	free(route);
	remove_queue(&q);
}
