#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *next;
} node_t;

void print_list(node_t *graph, int N) {
	for (int i = 0; i < N; ++i) {
		node_t *ip = graph + i;
		while (ip) {
			printf("%2d ", ip->val);
			ip = ip->next;
		}
		printf("\n");
	}
}


node_t *create_node(int val) {
	node_t *n = malloc(sizeof(node_t));
	n->val = val;
	n->next = NULL;
	return n;
}

void add_to_list(node_t *n, int val) {
	while (n->next) {
		n = n->next;
	}
	n->next = create_node(val);
}

void init_graph(node_t *graph, int N) {
	for (int i = 0; i < N; ++i) {
		graph[i].val = i + 1;
	}
}

void dfs(node_t *graph, node_t *node, int *parents) {
	node_t *i = node;
	while (i->next) {
		int next = i->next->val - 1;
		if (!parents[next]) {
			parents[next] = node->val;
			dfs(graph, graph + next, parents);
		}
		i = i->next;
	}
}

void free_graph(node_t *graph, int N) {
	for (int i = 0; i < N; ++i) {
		node_t *ip = graph[i].next;
		while (ip) {
			node_t *tmp = ip->next;
			free(ip);
			ip = tmp;
		}
	}
	free(graph);
}

int main(void) {
	int N;
	scanf("%d", &N);

	node_t *graph = malloc(sizeof(node_t) * N);
	init_graph(graph, N);
	for (int i = 1; i < N; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		add_to_list(&graph[a - 1], b);
		add_to_list(&graph[b - 1], a);
	}

	int *parents = calloc(N, sizeof(int));
	parents[0] = -1;
	dfs(graph, graph, parents);

	for (int i = 1; i < N; ++i) {
		printf("%d\n", parents[i]);
	}

	free_graph(graph, N);
	free(parents);
}
