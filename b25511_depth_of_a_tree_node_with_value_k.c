#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

typedef struct node {
	int val;
	struct node *next;
} node_t;

node_t *create_node(int val) {
	node_t *node = (node_t *)malloc(sizeof(node_t));
	node->val = val;
	node->next = NULL;
	return node;
}

void add_to_list(node_t *head, int val) {
	node_t *p = head;
	while (p->next) {
		p = p->next;
	}
	p->next = create_node(val);
}

int dfs(node_t *graph, node_t *node, int k, int *level) {
	if (node->val == k) {
		return 1;
	}

	node_t *i = node->next;
	while (i) {
		if (dfs(graph, graph + i->val, k, level)) {
			++(*level);
			return 1;
		}
		i = i->next;
	}
	return 0;
}

int main(void) {
	int n, k;
	scanf("%d %d", &n, &k);
	node_t graph[MAX] = { 0, };

	for (int i = 1; i < n; ++i) {
		int p, c;
		scanf("%d %d", &p, &c);
		add_to_list(&graph[p], c);
	}

	for (int i = 0; i < n; ++i) {
		int v;
		scanf("%d", &v);
		graph[i].val = v;
	}

	int level = 0;
	dfs(graph, graph, k, &level);
	printf("%d\n", level);
}
