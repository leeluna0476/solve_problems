#include <stdio.h>

#define MAX 300001
//typedef struct node {
//	int left;
//	int right;
//	int s;
//} node_t;

typedef struct node {
	int val;
	int s;
} node_t;
unsigned long long c = 0;
int n;
node_t tree[MAX];
//int l = 300000;
//int u = 1;

//void insert_bst(int *node, int key) {
//	if (!*node) {
//		*node = key;
//		if (key < l) {
//			l = key;
//		}
//		if (key > u) {
//			u = key;
//		}
//		return;
//	}
//	if (key > u) {
//		tree[u].right = key;
//		tree[key].s += tree[u].s + 1;
//		c += tree[key].s;
//		u = key;
//	}
//	else if (key < l) {
//		tree[l].left = key;
//		tree[key].s = tree[l].s + 1;
//		c += tree[key].s;
//		l = key;
//	}
//	else {
//		++c;
//		tree[key].s = tree[*node].s + 1;
//		if (key < *node) {
//			insert_bst(&(tree[*node].left), key);
//		}
//		else {
//			insert_bst(&(tree[*node].right), key);
//		}
//	}
//}

int main(void) {
	scanf("%d", &n);
	int root = 0;
	int *kp = keys;
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
//		insert_bst(&root, x);
		printf("%llu\n", c);
	}
}
