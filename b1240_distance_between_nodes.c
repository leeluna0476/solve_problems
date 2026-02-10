#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

typedef struct node {
	unsigned short no;
	unsigned long dist;
	struct node *next;
} node_t;

node_t *create_node(unsigned short no, unsigned long dist) {
	node_t *n = malloc(sizeof(node_t));
	n->no = no;
	n->dist = dist;
	n->next = NULL;
	return n;
}

void add_to_list(node_t *n, unsigned short no, unsigned long dist) {
	while (n->next) {
		n = n->next;
	}
	n->next = create_node(no, dist);
}

void init_graph(node_t *graph, int N) {
	for (int i = 0; i < N; ++i) {
		graph[i].no = i;
		graph[i].dist = 0;
	}
}

char dfs(node_t *graph, unsigned short a, unsigned short b, unsigned long *dist, char *visited) {
	visited[a] = 1;
	if (a == b) {
		return 1;
	}
	
	node_t *i = &graph[a];
	while (i) {
		if (i->dist && !visited[i->no] && dfs(graph, i->no, b, dist, visited)) {
			*dist += i->dist;
			return 1;
		}
		i = i->next;
	}

	return 0;
}

int main(void) {
	unsigned short N, M;
	scanf("%hu %hu", &N, &M);

	node_t *graph = malloc(sizeof(node_t) * N);
	init_graph(graph, N);
	for (unsigned short i = 1; i < N; ++i) {
		unsigned short a, b;
		unsigned long dist;
		scanf("%hu %hu %lu", &a, &b, &dist);
		--a;
		--b;
		add_to_list(&graph[a], b, dist);
		add_to_list(&graph[b], a, dist);
	}

	char visited[MAX] = { 0, };
	for (unsigned short i = 0; i < M; ++i) {
		unsigned short a, b;
		scanf("%hu %hu", &a, &b);
		--a;
		--b;
		unsigned long dist = 0;
		dfs(graph, a, b, &dist, visited);
		memset(visited, 0, sizeof(visited));
		printf("%lu\n", dist);
	}
}
