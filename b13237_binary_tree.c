#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	int depth;
	struct node *child1;
	struct node *child2;
} node_t;

void add_child(node_t *tree, int parent, int child) {
	if (!tree[parent].child1) {
		tree[parent].child1 = &tree[child];
	}
	else {
		tree[parent].child2 = &tree[child];
	}
}

void dfs(node_t *tree, node_t *node, int parent_depth) {
	if (!node) {
		return;
	}
	node->depth = parent_depth + 1;
	dfs(tree, node->child1, node->depth);
	dfs(tree, node->child2, node->depth);
}

int main(void) {
	int n;
	scanf("%d", &n);

	node_t *tree = calloc(n, sizeof(node_t));
	node_t *root;
	for (int i = 0; i < n; ++i) {
		int parent;
		scanf("%d", &parent);
		if (parent == -1) {
			root = &tree[i];
		}
		else {
			add_child(tree, parent - 1, i);
		}
	}

	dfs(tree, root, -1);

	for (int i = 0; i < n; ++i) {
		printf("%d\n", tree[i].depth);
	}
}
