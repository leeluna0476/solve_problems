#include <stdio.h>

#define MAX 100
#define QMAX 1000001

typedef struct pos {
	char x;
	char y;
	char z;
} pos_t;

typedef struct queue {
	pos_t storage[QMAX];
	int front;
	int back;
} queue_t;

void init_queue(queue_t *q) {
	q->front = 0;
	q->back = 0;
}

char is_empty(queue_t *q) {
	return q->front == q->back;
}

char is_full(queue_t *q) {
	return (q->back + 1) % QMAX == q->front;
}

void push_back(queue_t *q, pos_t val) {
	if (!is_full(q)) {
		q->back = (q->back + 1) % QMAX;
		q->storage[q->back] = val;
	}
}

pos_t pop_front(queue_t *q) {
	pos_t ret = { -1, -1, -1 };
	if (!is_empty(q)) {
		q->front = (q->front + 1) % QMAX;
		ret = q->storage[q->front];
	}
	return ret;
}

char in_box(pos_t pos, char m, char n, char h) {
	return pos.x >= 0 && pos.x < m && pos.y >= 0 && pos.y < n && pos.z >= 0 && pos.z < h;
}

char all_ripen(int (*box)[MAX][MAX], char m, char n, char h) {
	for (char i = 0; i < h; ++i) {
		for (char j = 0; j < n; ++j) {
			for (char k = 0; k < m; ++k) {
				if (box[i][j][k] == 0) {
					return 0;
				}
			}
		}
	}
	return 1;
}

int bfs(int (*box)[MAX][MAX], char m, char n, char h, queue_t *q) {
	char diff[6][3] = {
		{ -1, 0, 0 },
		{ 1, 0, 0 },
		{ 0, -1, 0 },
		{ 0, 1, 0 },
		{ 0, 0, -1 },
		{ 0, 0, 1 },
	};
	int maxday = !is_empty(q);

	while (!is_empty(q)) {
		pos_t pos = pop_front(q);
		int day = box[pos.z][pos.y][pos.x];
		if (day > maxday) {
			maxday = day;
		}

		for (char i = 0; i < 6; ++i) {
			pos_t npos = { pos.x + diff[i][0], pos.y + diff[i][1], pos.z + diff[i][2] };
			if (in_box(npos, m, n, h) && !box[npos.z][npos.y][npos.x]) {
				box[npos.z][npos.y][npos.x] = day + 1;
				push_back(q, npos);
			}
		}
	}

	return maxday - 1;
}

int ripen_tomatoes(int (*box)[MAX][MAX], char m, char n, char h, queue_t *q) {
	int answer = bfs(box, m, n, h, q);

	if (!all_ripen(box, m, n, h)) {
		answer = -1;
	}

	return answer;
}

int main(void) {
	char m, n, h;
	scanf("%hhd %hhd %hhd", &m, &n, &h);
	int box[MAX][MAX][MAX];
	queue_t q;
	init_queue(&q);
	for (char i = 0; i < h; ++i) {
		for (char j = 0; j < n; ++j) {
			for (char k = 0; k < m; ++k) {
				scanf("%d", &box[i][j][k]);
				if (box[i][j][k] == 1) {
					pos_t pos = { k, j, i };
					push_back(&q, pos);
				}
			}
		}
	}

	printf("%d\n", ripen_tomatoes(box, m, n, h, &q));
}
