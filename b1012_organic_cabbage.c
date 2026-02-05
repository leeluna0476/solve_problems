#include <stdio.h>

typedef struct pos {
	int x;
	int y;
} pos_t;

#define MAX 2500

typedef struct stack {
	pos_t storage[MAX];
	int top;
} stack_t;

void init(stack_t *stk) {
	stk->top = -1;
}

void push(stack_t *stk, pos_t pos) {
	++(stk->top);
	if (stk->top < MAX) {
		stk->storage[stk->top] = pos;
	}
}

pos_t pop(stack_t *stk) {
	if (stk->top > -1) {
		return stk->storage[(stk->top)--];
	}
	else {
		pos_t pos = { -1, -1 };
		return pos;
	}
}

pos_t find_start(int (*field)[50], int M, int N, pos_t start) {
	int y = start.y;
	int x = start.x;
	pos_t pos = { -1, -1 };
	while (y < N) {
		while (x < M) {
			if (field[y][x]) {
				pos.x = x;
				pos.y = y;
				return pos;
			}
			++x;
		}
		x = 0;
		++y;
	}
	return pos;
}

void push_pos(int (*field)[50], int M, int N, pos_t pos, stack_t *stk) {
	if (pos.x >= 0 && pos.x < M && pos.y >= 0 && pos.y < N && field[pos.y][pos.x]) {
		push(stk, pos);
	}
}

void dfs(int (*field)[50], int M, int N, pos_t start) {
	stack_t stk;
	init(&stk);
	pos_t pos = start;
	int diff[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 }, };
	while (pos.x != -1) {
		field[pos.y][pos.x] = 0;
		for (int i = 0; i < 4; ++i) {
			pos_t new_pos = { pos.x + diff[i][0], pos.y + diff[i][1] };
			push_pos(field, M, N, new_pos, &stk);
		}
		pos = pop(&stk);
	}
}

int worms(int (*field)[50], int M, int N) {
	pos_t start = { 0, 0 };
	start = find_start(field, M, N, start);
	int cnt = 0;
	while (start.x != -1) {
		dfs(field, M, N, start);
		++cnt;
		start = find_start(field, M, N, start);
	}
	return cnt;
}

int main(void) {
	int T, M, N, K;
	scanf("%d", &T);
	for (int t = 0; t < T; ++t) { // testcases
		int field[50][50] = { 0, };
		scanf("%d %d %d", &M, &N, &K);
		for (int k = 0; k < K; ++k) {
			int x, y;
			scanf("%d %d", &x, &y);
			field[y][x] = 1;
		}
		printf("%d\n", worms(field, M, N));
	}
}
