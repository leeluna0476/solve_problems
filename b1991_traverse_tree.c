#include <stdio.h>

#define MAX 26

// spelling 틀림 이슈 ㅎ
void preorder_traversal(char (*tree)[2], char node) {
	if (node == '.') {
		return;
	}
	putchar(node);
	preorder_traversal(tree, tree[node - 'A'][0]);
	preorder_traversal(tree, tree[node - 'A'][1]);
	if (node == 'A') {
		printf("\n");
	}
}

void inorder_traversal(char (*tree)[2], char node) {
	if (node == '.') {
		return;
	}
	inorder_traversal(tree, tree[node - 'A'][0]);
	putchar(node);
	inorder_traversal(tree, tree[node - 'A'][1]);
	if (node == 'A') {
		printf("\n");
	}
}

void postorder_traversal(char (*tree)[2], char node) {
	if (node == '.') {
		return;
	}
	postorder_traversal(tree, tree[node - 'A'][0]);
	postorder_traversal(tree, tree[node - 'A'][1]);
	putchar(node);
	if (node == 'A') {
		printf("\n");
	}
}

int main(void) {
	char N;
	scanf("%hhd", &N);
	char tree[MAX][2] = { 0, };
	for (char i = 0; i < N; ++i) {
		char a, b, c;
		scanf(" %c %c %c", &a, &b, &c);
		tree[a - 'A'][0] = b;
		tree[a - 'A'][1] = c;
	}

	preorder_traversal(tree, 'A');
	inorder_traversal(tree, 'A');
	postorder_traversal(tree, 'A');
}
