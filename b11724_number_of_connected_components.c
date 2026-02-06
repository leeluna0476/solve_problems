#include <stdio.h>

#define MAX 1000

int dfs(char (*graph)[MAX], int n, int node) {
	static char visited[MAX];
	int ret = 0;
	visited[node] = 1;
	for (int i = 0; i < n; ++i) {
		if (graph[node][i]) {
			if (node == i) {
				ret = 1;
				break;
			}
			else if (!visited[i]) {
				ret = 1;
				dfs(graph, n, i);
			}
		}
	}
	return ret;
}

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	char graph[MAX][MAX] = { 0, };
	for (int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		--u;
		--v;
		graph[u][v] = 1;
		graph[v][u] = 1;
	}

	for (int i = 0; i < n; ++i) {
		int con = 0;
		for (int j = 0; j < n; ++j) {
			if (graph[i][j]) {
				con = 1;
				break;
			}
		}
		if (!con) {
			graph[i][i] = 1;
		}
	}

	int d = 0;
	for (int i = 0; i < n; ++i) {
		if (dfs(graph, n, i)) {
			++d;
		}
	}
	printf("%d\n", d);
}
