#include <stdio.h>

#define MAX 50

char dfs(char (*graph)[MAX], char N, char node, char delete, char *leaves) {
	if (node == delete) {
		return 1;
	}

	char none = 1;
	for (char i = 0; i < N; ++i) {
		if (graph[node][i] && !dfs(graph, N, i, delete, leaves)) {
			none = 0;
		}
	}
	if (none) {
		++(*leaves);
	}
	return 0;
}

int main(void) {
	char graph[MAX][MAX] = { 0, };
	char N;
	scanf("%hhd", &N);
	char root;
	for (char i = 0; i < N; ++i) {
		char p;
		scanf("%hhd", &p);
		if (p == -1) {
			root = i;
		}
		else {
			graph[p][i] = 1;
		}
	}
	char delete;
	scanf("%hhd", &delete);

	char leaves = 0;
	dfs(graph, N, root, delete, &leaves);
	printf("%hhd\n", leaves);
}
