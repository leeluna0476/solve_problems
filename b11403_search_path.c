#include <stdio.h>

#define MAX 100

char graph[MAX][MAX];
char answer[MAX][MAX];
int n;

void dfs(int start, int node, int cnt) {
	if (cnt) {
		answer[start][node] = 1;
		if (start == node) {
			return;
		}
	}

	for (int i = 0; i < n; ++i) {
		if (graph[node][i] && !answer[start][i]) {
			dfs(start, i, cnt + 1);
		}
	}
}

void record_path(int n) {
	for (int i = 0; i < n; ++i) {
		dfs(i, i, 0);
	}
}

int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%hhd", &graph[i][j]);
		}
	}

	record_path(n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%hhd ", answer[i][j]);
		}
		printf("\n");
	}
}
