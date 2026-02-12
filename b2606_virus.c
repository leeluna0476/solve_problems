#include <stdio.h>

#define MAX 100

void dfs(char (*graph)[MAX], char n, char node, char *infected) {
	static char visited[MAX];
	visited[node] = 1;
	++(*infected);
	for (char i = 0; i < n; ++i) {
		if (graph[node][i] && !visited[i]) {
			dfs(graph, n, i, infected);
		}
	}
}

int main(void) {
	char n;
	short m;
	scanf("%hhd %hd", &n, &m);
	char graph[MAX][MAX] = { 0, };
	for (short i = 0; i < m; ++i) {
		char a, b;
		scanf("%hhd %hhd", &a, &b);
		--a;
		--b;
		graph[a][b] = 1;
		graph[b][a] = 1;
	}

	char infected = -1;
	dfs(graph, n, 0, &infected);
	printf("%hhd\n", infected);
}
