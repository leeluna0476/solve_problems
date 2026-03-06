#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	int key;
	int height;
	int depth;
	struct node *left;
	struct node *right;
} node_t;

unsigned long long cnt;

#define max(a, b) (a > b ? a : b)

node_t *create_node(int key, int d) {
	node_t *n = malloc(sizeof(node_t));
	n->key = key;
	n->height = 1;
	n->depth = d;
	n->left = NULL;
	n->right = NULL;
	return n;
}

int calc_height(node_t *root) {
	if (!root) {
		return 0;
	}
	return root->height;
}

int calc_balance(node_t *root) {
	int rl = calc_height(root->left);
	int rr = calc_height(root->right);
	return rl - rr;
}

node_t *rotateLL(node_t *A) {
	node_t *B = A->left;
	A->left = B->right;
	B->right = A;
	A->height = max(calc_height(A->left), calc_height(A->right)) + 1;
	B->height = max(calc_height(B->left), calc_height(B->right)) + 1;
	return B;
}

node_t *rotateRR(node_t *A) {
	node_t *B = A->right;
	A->right = B->left;
	B->left = A;
	A->height = max(calc_height(A->left), calc_height(A->right)) + 1;
	B->height = max(calc_height(B->left), calc_height(B->right)) + 1;
	return B;
}

node_t *rotateLR(node_t *A) {
	A->left = rotateRR(A->left);
	return rotateLL(A);
}

node_t *rotateRL(node_t *A) {
	A->right = rotateLL(A->right);
	return rotateRR(A);
}

node_t *insert(node_t *root, int key, int d) {
	if (!root) {
		return create_node(key, d);
	}
	node_t *n = NULL;
	if (key < root->key) {
		n = insert(root->left, key, d);
		root->left = n;
		root->height = max(root->height, n->height + 1);
	}
	else if (key > root->key) {
		n = insert(root->right, key, d);
		root->right = n;
		root->height = max(root->height, n->height + 1);
	}
	else {
		return root;
	}

	int balance = calc_balance(root);
	if (balance > 1) {
		if (key < root->left->key) { // LL
			root = rotateLL(root);
		}
		else if (key > root->left->key) { // LR
			root = rotateLR(root);
		}
	}
	else if (balance < -1) {
		if (key < root->right->key) { // RL
			root = rotateRL(root);
		}
		else if (key > root->right->key) { // RR
			root = rotateRR(root);
		}
	}
	return root;
}

void find_ab(node_t *root, int key, int *a, int *b) {
	if (!root) {
		return;
	}
	if (root->key > key) {
		*b = root->depth;
		find_ab(root->left, key, a, b);
	}
	else {
		*a = root->depth;
		find_ab(root->right, key, a, b);
	}
}

int imbalanced_depth(node_t *root, int key) {
	int a = -1;
	int b = -1;
	find_ab(root, key, &a, &b);
	return max(a, b) + 1;
}

void print_bst(node_t *root) {
	if (!root) {
		return;
	}
	printf("[%d]: [%d]\n", root->key, root->height);
	print_bst(root->left);
	print_bst(root->right);
}

int main(void) {
	node_t *root = NULL;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		int d = imbalanced_depth(root, x);
		cnt += d;
		root = insert(root, x, d);
		printf("%llu\n", cnt);
	}
}
