#include <stdio.h>

#define MAX 100

int dfs(char (*graph)[MAX], int n, int p1, int p2, int *d) {
	static char visited[MAX];
	visited[p1] = 1;
	for (int i = 0; i < n; ++i) {
		if (graph[p1][i] && !visited[i]) {
			if (i == p2 || dfs(graph, n, i, p2, d)) {
				++(*d);
				return 1;
			}
		}
	}
	return 0;
}

int main(void) {
	int n, p1, p2, m;
	char graph[MAX][MAX] = { 0, };

	scanf("%d %d %d %d", &n, &p1, &p2, &m);
	for (int i = 0; i < m; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		--x;
		--y;
		graph[x][y] = 1;
		graph[y][x] = 1;
	}
	int d = 0;
	dfs(graph, n, p1 - 1, p2 - 1, &d);
	printf("%d\n", d ? d : -1);
}
