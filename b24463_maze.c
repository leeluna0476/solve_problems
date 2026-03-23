#include <stdio.h>

#define MAX 2001

typedef struct pos {
	int x;
	int y;
} pos_t;

int n;
int m;

void find_edge(char (*map)[MAX], pos_t *start, pos_t *end) {
	pos_t pos[2];
	pos_t *p = pos;

	// 출입구는 하나씩만 주어진다.
	// p < pos + 2 보장됨.
	for (int i = 0; i < n; ++i) {
		if (map[i][0] == '.') {
			p->x = 0;
			p->y = i;
			++p;
		}
		else if (map[i][m - 1] == '.') {
			p->x = m - 1;
			p->y = i;
			++p;
		}
	}

	for (int i = 0; i < m; ++i) {
		if (map[0][i] == '.') {
			p->x = i;
			p->y = 0;
			++p;
		}
		else if (map[n - 1][i] == '.') {
			p->x = i;
			p->y = n - 1;
			++p;
		}
	}
	*start = pos[0];
	*end = pos[1];
}

int in_range(pos_t *pos) {
	return pos->x >= 0 && pos->x < m && pos->y >= 0 && pos->y < n;
}

int dfs(char (*map)[MAX], pos_t *start, pos_t *end, pos_t *pos) {
	map[pos->y][pos->x] = '@';
	if (pos->x == end->x && pos->y == end->y) {
		return 1;
	}

	int diff[4][2] = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };
	for (int i = 0; i < 4; ++i) {
		pos_t npos = { pos->x + diff[i][0], pos->y + diff[i][1] };
		if (in_range(&npos) && map[npos.y][npos.x] == '.') {
			if (dfs(map, start, end, &npos)) {
				return 1;
			}
		}
	}

	map[pos->y][pos->x] = '.';
	return 0;
}

void unused_path(char (*map)[MAX]) {
	pos_t start, end;
	find_edge(map, &start, &end);
	dfs(map, &start, &end, &start);
}

int main(void) {
	scanf("%d %d", &n, &m);

	char map[MAX][MAX];
	for (int i = 0; i < n; ++i) {
		getchar();
		for (int j = 0; j < m; ++j) {
			map[i][j] = getchar();
		}
	}

	unused_path(map);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			switch (map[i][j]) {
				case '@': putchar('.'); break;
				case '.': putchar('@'); break;
				default: putchar(map[i][j]); break;
			}
		}
		putchar('\n');
	}
}
