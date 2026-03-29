#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
} node_t;

node_t *create_node(int data) {
	node_t *n = (node_t *)malloc(sizeof(node_t));
	n->data = data;
	n->left = NULL;
	n->right = NULL;
	return n;
}

void insert_node(node_t **head, int data) {
	if (!*head) {
		*head = create_node(data);
        return;
	}

	if (data < (*head)->data) {
		insert_node(&(*head)->left, data);
	}
	else if (data > (*head)->data) {
		insert_node(&(*head)->right, data);
	}
}

void remove_tree(node_t *head) {
	if (!head) {
		return;
	}

	remove_tree(head->left);
	remove_tree(head->right);
	free(head);
}

void postorder_traversal(node_t *head) {
	if (!head) {
		return;
	}

	postorder_traversal(head->left);
	postorder_traversal(head->right);
	printf("%d\n", head->data);
}

int main(void) {
	int x;
	node_t *head = NULL;
	while (scanf("%d", &x) != -1) {
		insert_node(&head, x);
	}

	postorder_traversal(head);
	remove_tree(head);
}
