#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
	char **storage;
	int n;
	char *visited;
} graph_t;

graph_t *init_graph(int n) {
	graph_t *g = (graph_t *)calloc(n, sizeof(graph_t));
	g->storage = (char **)calloc(n, sizeof(char *));
	for (int i = 0; i < n; ++i) {
		g->storage[i] = (char *)calloc(n, sizeof(char));
	}
	g->n = n;
	g->visited = (char *)calloc(n, sizeof(char));

	return g;
}

void free_graph(graph_t *g) {
	for (int i = 0; i < g->n; ++i) {
		free(g->storage[i]);
	}
	free(g->storage);
	free(g->visited);
	free(g);
}

void dfs(graph_t *graph, int person, char level, int *guest) {
	graph->visited[person] = 1;
	if (level > 2) {
		return;
	}
	for (int i = 0; i < graph->n; ++i) {
		if (graph->storage[person][i]) {
			if (!graph->visited[i]) {
				++(*guest);
			}
			dfs(graph, i, level + 1, guest);
		}
	}
}

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m);

	graph_t *graph = init_graph(n);

	for (int i = 0; i < m; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		graph->storage[a - 1][b - 1] = 1;
		graph->storage[b - 1][a - 1] = 1;
	}

	int guest = 0;
	dfs(graph, 0, 1, &guest);
	printf("%d\n", guest);

	free_graph(graph);
}
