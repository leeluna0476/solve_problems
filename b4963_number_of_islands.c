#include <stdio.h>

typedef struct pos {
	int x;
	int y;
} pos_t;

void dfs(char (*map)[50], pos_t size, pos_t pos) {
	if (pos.x < 0 || pos.x >= size.x || pos.y < 0 || pos.y >= size.y || !map[pos.y][pos.x]) {
		return;
	}

	map[pos.y][pos.x] = 0;

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i || j) {
				pos_t new_pos = { pos.x + j, pos.y + i };
				dfs(map, size, new_pos);
			}
		}
	}
}

pos_t find_start(char (*map)[50], pos_t size, pos_t start) {
	int i = start.y;
	int j = start.x;
	pos_t pos = { -1, -1 };
	while (i < size.y) {
		while (j < size.x) {
			if (map[i][j]) {
				pos.x = j;
				pos.y = i;
				return pos;
			}
			++j;
		}
		j = 0;
		++i;
	}
	return pos;
}

int main(void) {
	pos_t size;
	char map[50][50];
	while (42) {
		scanf("%d %d", &size.x, &size.y);
		if (!size.x) {
			break;
		}
		for (int i = 0; i < size.y; ++i) {
			for (int j = 0; j < size.x; ++j) {
				scanf("%hhd", &map[i][j]);
			}
		}

		int n = 0;
		pos_t pos = { 0, 0 };
		pos = find_start(map, size, pos);
		while (pos.x != -1) {
			dfs(map, size, pos);
			++n;
			pos = find_start(map, size, pos);
		}
		printf("%d\n", n);
	}
}
